// this file added by yongming.li for node data

#include "redis.h"
#include <math.h>

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "mydump.h"
#include <stdlib.h>

#include <errno.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/ipc.h>  
#include <sys/stat.h>  
#include <sys/msg.h> 

#include "credis.h"
#include "mychat.h"
#include "myuser.h"
#include "mydebug.h"

/*
use hash dict to speed up search  
*/

void  chatNotifyUserInfo(redisClient *c)
{

    // added by yongming.li for nothing should to notify  for invalid client 
    if(c->isvaliduser==0  || c->isvalidnode==0)
    {
    	     return;
    }
    //////////////////////////////////////////////////////////
    if(c->mynode_type==MYNODE_TYPE_USER)
    {
         chat_sendtoclient("userinfo",c,c->username,"all","off",MYNODE_TYPE_USER);
         chatSetOrGetUserInfo(c->username,"off",OPERATION_SET_INFO);
    }
    if(c->mynode_type==MYNODE_TYPE_NODE)
    {
         chat_sendtoclient("nodeinfo",c,c->nodename,c->username,"off",MYNODE_TYPE_USER);
         chatSetOrGetNodeInfo(c->username,c->nodename,"off",OPERATION_SET_INFO);
    }

}

// -lmysqlclient  for gcc 
// yongming.li for command sync

//  if ((o = hashTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;

void mychat_reply(redisClient *c,char * str)
{
   char buf[256]={0x00};
   sprintf(buf,"+%s\r\n",str);
   addReplyString(c,buf,strlen(buf));
   return;
}

void chat_sendtoclient(char * tag ,redisClient *c , char * from , char * to ,char * message, unsigned char  toType)
{
    int numclients = listLength(server.clients);
    redisClient *ctemp;
    listNode *head;
    int i=0; 
    int  slen;
    char sbuf[1024];

    //printf(" from  %-20s  to  %-20s  \r\n",from,to);
    while(i++<numclients) {
        listRotate(server.clients);
        head = listFirst(server.clients);
        ctemp = listNodeValue(head);
        if(ctemp==NULL)
        { 
           break;
        }
        //  so i think it is better ths , a node cant talk to any other node 
         if(ctemp->mynode_type!= toType)
         {
             continue;
         }

         if(toType==MYNODE_TYPE_NODE)
         {
              if (strcmp(to,"all")  &&  strcmp(ctemp->nodename,to)   )
             {
                  continue;
             }
         }

         if(toType==MYNODE_TYPE_USER)
         {
              if (strcmp(to,"all")  &&  strcmp(ctemp->username,to)   )
             {
                  continue;
             }
         }
         
        slen = snprintf(sbuf,sizeof(sbuf),"%s ok %s %s\r\n",tag,from,message);
        addReplyString(ctemp,sbuf,slen);
        
        //break;
    }
    
}

//  for chat
//  chat   "somebody"   "message"
//  chat   register  name password
//  chat   login  name userword
//  chat   say   otherbodyname  messagebody
//  chat   userinfo   0   0

//  for node control or update data / state

//  chat register name userid

int chat_register(redisClient *c) {
    robj *set;
    if ((set = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL)
    	{
    	    return 0;
    	}
    
        
    c->argv[2] = tryObjectEncoding(c->argv[2]);
    if (setTypeIsMember(set,c->argv[2]))
        //addReply(c,shared.cone);
        return  1;
    else
        //addReply(c,shared.czero);
        return 0;
}

void chatSay(redisClient *c)
{

    if(!(c->isvaliduser))
    {
        //addReplyError(c,"chat fail ");
        addReplyString(c,"chat  fail\r\n",strlen("chat  fail\r\n"));
        return;
    }

    chat_sendtoclient("chat",c,c->username,c->argv[2]->ptr,c->argv[3]->ptr,MYNODE_TYPE_USER);
    return;
}
void chatLogin(redisClient *c)
{
    int ret =0;
    char buf[256]={0x00};
    char state[256]={0x00};
    
    ret=is_valid_user(c->argv[2]->ptr,c->argv[3]->ptr);
    if(ret<=0)
    {
    	    //addReplyError(c,"chat  , sorry , wrong username or password ,please check carefully");
    	    //mychat_reply(c,"fail");
    	    addReplyString(c,"login fail wrongNameorPasswd\r\n",strlen("login fail wrongNameorPasswd\r\n"));
    	    c->isvaliduser=0;
    	    c->isvalidnode=0;
    	    return;
    }

    chatSetOrGetUserInfo(c->argv[2]->ptr,state,OPERATION_GET_INFO);
    if(!strcmp(state,"on"))
    {
         addReplyString(c,"login fail alreadylogin\r\n",strlen("login fail alreadylogin\r\n"));
         printf("%s , you have already login \r\n",c->argv[2]->ptr);
         c->isvaliduser=0;
    	    c->isvalidnode=0;
    	    return;
    }

    
    c->isvaliduser=1;
    c->isvalidnode=1;
    c->mynode_type=MYNODE_TYPE_USER;
    //mychat_reply(c,"ok");

    chatSetOrGetUserInfo(c->argv[2]->ptr,"on",OPERATION_SET_INFO);
    
    chat_sendtoclient("userinfo",c,c->argv[2]->ptr,"all","on",MYNODE_TYPE_USER);
    sprintf(c->username,"%s",c->argv[2]->ptr);
    sprintf(c->password,"%s",c->argv[3]->ptr);
    sprintf(buf,"login ok %s\r\n",getUseridByName(c));
    addReplyString(c,buf,strlen(buf));
    getAllNodeInfo(c);
    chatUserInfo(c);
    //printf("login success , c->username is %s and c->password is %s \r\n",c->username,c->password);
    return;
}

void nodeLogin(redisClient *c)
{
    char * username=NULL;
    char * userid=NULL;
    char * nodename=NULL;
    char buf[256]={0x00};
    char cmd[256]={0x00};
    char state[256]={0x00};
    int nodesize=0;
    printf("nodeLogin %s  %s \r\n",c->argv[2]->ptr,c->argv[3]->ptr);

    userid=c->argv[2]->ptr;
    nodename=c->argv[3]->ptr;
    username=getNameByUserid(userid);
    if(username==NULL)
    {
         addReplyString(c,"login fail wrongNameorPasswd\r\n",strlen("login fail wrongNameorPasswd\r\n"));
    	    c->isvaliduser=0;
    	    c->isvalidnode=0;
    	    return;
    }
    nodesize=getUserNodeSize(username);
    printf("nodesize is %d \r\n",nodesize);

    chatSetOrGetNodeInfo(c->username,c->nodename,state,OPERATION_GET_INFO);
    if(!strcmp(state,"on"))
    {
         addReplyString(c,"login fail alreadylogin\r\n",strlen("login fail alreadylogin\r\n"));
         printf("%s , you have already login \r\n",c->argv[2]->ptr);
         c->isvaliduser=0;
    	    c->isvalidnode=0;
    	    return;
    }

    int retInsertNode = insertNodeToUserInfo(username,nodename);
    if(retInsertNode== (-1))
    {
          sprintf(buf,"login fail toomanynode\r\n");
          addReplyString(c,buf,strlen(buf));
    	    c->isvaliduser=0;
    	    c->isvalidnode=0;
    	    return;  	
    }
    if(retInsertNode==1)
    {
            sprintf(cmd,"insert into node values('%s', '%s',  '0','0');",userid,nodename);
            mysqlRunCommand(cmd);
    }

    sprintf(buf,"login ok %s\r\n",username);
    addReplyString(c,buf,strlen(buf));
    c->isvaliduser=1;
    c->isvalidnode=1;
    c->mynode_type=MYNODE_TYPE_NODE;


    sprintf(c->username,"%s",username);
    sprintf(c->userid,"%s",userid);
    sprintf(c->nodename,"%s",nodename);
    chat_sendtoclient("nodeinfo",c,c->nodename,c->username,"on",MYNODE_TYPE_USER);


    chatSetOrGetNodeInfo(c->username,c->nodename,"on",OPERATION_SET_INFO);

    return;
}

//  node login 3ee50503b2cd6e8ac0ebfc486054f8ee tv
//  node say   self  message
//  node say   tv  message


void nodeSay(redisClient *c)
{
    if(c->mynode_type==MYNODE_TYPE_USER)
    {
    	    chat_sendtoclient("node",c,c->username,c->argv[2]->ptr,c->argv[3]->ptr,MYNODE_TYPE_NODE);
    }
    if(c->mynode_type==MYNODE_TYPE_NODE)
    {
    	    chat_sendtoclient("node",c,c->nodename,c->username,c->argv[3]->ptr,MYNODE_TYPE_USER);
    }
    return;
}
void nodeCommand(redisClient *c) 
{
      if(!strcmp(c->argv[1]->ptr,"login"))
     {
     	    nodeLogin(c);
     	    return;
     }
     if(!(c->isvalidnode))
    {
        addReplyString(c,"node fail nologin\r\n",strlen("node fail nologin\r\n\r\n"));
        return;
    }
     /////////////////////////////////////////////////////////////////////
     if(!strcmp(c->argv[1]->ptr,"say"))
     {
     	    nodeSay(c);
     	    return;
     }
     if(!strcmp(c->argv[1]->ptr,"heartbeat"))
     {
          // added by yongming.li for update lastinteraction time
     	    return;
     }
     
     return;
}
void chatCommand(redisClient *c) 
{
     if(!strcmp(c->argv[1]->ptr,"login"))
     {
     	    chatLogin(c);
     	    return;
     }
     if(!strcmp(c->argv[1]->ptr,"say"))
     {
     	    chatSay(c);
     	    return;
     }
     if(!strcmp(c->argv[1]->ptr,"userinfo"))
     {
     	    chatUserInfo(c);
     	    return;
     }
     if(!strcmp(c->argv[1]->ptr,"heartbeat"))
     {
           // added by yongming.li for update lastinteraction time
     	    return;
     }
      if(!strcmp(c->argv[1]->ptr,"debug"))
     {
         myDebugEntry(c);
     	    return;
     }
      if(!strcmp(c->argv[1]->ptr,"adduser"))
     {
         myAddUser(c);
     	    return;
     }

     
     // addReplyError(c,"chat  , sorry , invalid  command ( now only support : say logo regisgter)");
     return;
}


