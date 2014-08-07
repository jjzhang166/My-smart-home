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
 * wrong definitions
 */
static char *errChatInvalidUser = "user fail invalidUser\r\n";
static char *errChatTooBigMsg   = "user fail tooBigMessage\r\n";
static char *errWrongNameOrPwd  = "login fail wrongNameOrPasswd\r\n";
static char *errAlreadyLogin    = "login fail alreadyLogin\r\n";
static char *errTooManyNodes    = "login fail tooManyNode\r\n";
static char *errNodeNoLogin     = "node fail nologin\r\n";
static char *errUserNoLogin     = "user fail nologin\r\n";

// added by yongming.li for server heartbeat
static char * responseHeartBeat    = "server heartbeat r r r r\r\n";


#define    SEND_MESSAGE_TO_FAMILY           "family"

#define    NODE_LOGIN_CMD                          1
#define    NODE_LOGIN_USERID                     2
#define    NODE_LOGIN_NAME                        3
#define    NODE_SAY_NAME                            2



#define    CHAT_LOGIN_CMD                       1
#define    CHAT_LOGIN_NAME                     2
#define    CHAT_LOGIN_PASSWORD            3

#define    CHAT_SAY_NAME                         2
#define    CHAT_SAY_MESSAGE                   3
#define    CHAT_SAY_MESSAGEID                4
#define    CHAT_SAY_QOS                            5



void _chatSend(char *tag, redisClient *c, char *from, char *to, char *message, unsigned char toType,char * messageid ,char * qos);

/*
  use hash dict to speed up search
*/

void  chatNotifyUserInfo(redisClient *c)
{
    // added by yongming.li for nothing should to notify  for invalid client
    if(c->isvaliduser==0  || c->isvalidnode==0) {
        return;
    }
    //////////////////////////////////////////////////////////
    if(c->mynode_type==MYNODE_TYPE_USER) {
        _chatSend("userinfo",c,c->username,SEND_MESSAGE_TO_FAMILY,"off",MYNODE_TYPE_USER,"NULL","0");
        chatSetOrGetUserInfo(c->username,"off",OPERATION_SET_INFO);
    } else if(c->mynode_type==MYNODE_TYPE_NODE) {
        _chatSend("nodeinfo",c,c->nodename,SEND_MESSAGE_TO_FAMILY,"off",MYNODE_TYPE_USER,"NULL","0");
        chatSetOrGetNodeInfo(c->hostname,c->nodename,"off",OPERATION_SET_INFO);
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

void _chatSend(char *tag, redisClient *c, char *from, char *to, char *message, unsigned char toType , char * messageid ,char * qos) {
    listIter *iter;
    listNode *node;
    redisClient *cTemp =NULL;

    //printf(" from  %-20s  to  %-20s  \r\n",from,to);

    iter = listGetIterator(server.clients, AL_START_HEAD);
    
    while((node = listNext(iter)) != NULL) {
        int  slen = 0;
        char sbuf[1024] = {0};
        
        cTemp = listNodeValue(node);
        if (cTemp->mynode_type != toType) {
            continue;
        }

        #if  0
        if (MYNODE_TYPE_NODE == toType) {
            if ((strcmp(to, "all")) && (strcmp(c->nodename, to))) {
                continue;
            }
        } else if (MYNODE_TYPE_USER == toType) {
            if ((strcmp(to, "all")) && (strcmp(c->username, to))) {
                continue;
            }
        }
        #endif 
        if (MYNODE_TYPE_USER == toType)
        {
            if (!strcmp(to, SEND_MESSAGE_TO_FAMILY))
            	{
            	     if(strcmp(cTemp->hostname, c->hostname))
            	     	{
            	     	    continue;
            	     	}
            	}
            else
            	{
            	      if(strcmp(cTemp->username, to))
            	     	{
            	     	    continue;
            	     	}
            	}
        }

        if (MYNODE_TYPE_NODE == toType)
        {
            	 if(strcmp(cTemp->nodename, to))
            	 {
            	     	    continue;
            	 }
        }


        
        slen = snprintf(sbuf, sizeof(sbuf), "%s ok %s %s %s %s\r\n", tag, from, message,messageid,qos);
        addReplyString(cTemp, sbuf, slen);
    }

    listReleaseIterator(iter);
}



int chat_register(redisClient *c) {
    robj *set;
    if ((set = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL) {
        return 0;
    }

    c->argv[2] = tryObjectEncoding(c->argv[2]);
    if (setTypeIsMember(set,c->argv[2])) {
        //addReply(c,shared.cone);
        return  1;
    } else {
        //addReply(c,shared.czero);
        return 0;
    }
}

void chatSay(redisClient *c)
{
    if(!(c->isvaliduser)) {
        addReplyString(c, errChatInvalidUser, strlen(errChatInvalidUser));
        return;
    } else if ((strlen(c->argv[3]->ptr)) > MYCHAT_MAX_MESSAGE) {
        addReplyString(c, errChatTooBigMsg, strlen(errChatTooBigMsg));
        return;
    }

    _chatSend("user",c,c->username,c->argv[CHAT_SAY_NAME]->ptr,c->argv[CHAT_SAY_MESSAGE]->ptr,MYNODE_TYPE_USER,c->argv[CHAT_SAY_MESSAGEID]->ptr,c->argv[CHAT_SAY_QOS]->ptr);
    return;
}
void chatLogin(redisClient *c)
{
    int ret =0;
    char buf[256]={0x00};
    char state[256]={0x00};

        // modiefied by yongming.li for invalid client
    if(c->isvaliduser  || c->isvalidnode) {
		addReplyString(c, errAlreadyLogin, strlen(errAlreadyLogin));
		return;
    	}

    ret=is_valid_user(c->argv[CHAT_LOGIN_NAME]->ptr,c->argv[CHAT_LOGIN_PASSWORD]->ptr);
    if(ret<=0) {

        addReplyString(c, errWrongNameOrPwd, strlen(errWrongNameOrPwd));
        c->isvaliduser=0;
        c->isvalidnode=0;
        return;
    }

    chatSetOrGetUserInfo(c->argv[CHAT_LOGIN_NAME]->ptr,state,OPERATION_GET_INFO);
     if(!strcmp(state,"on")) {
        addReplyString(c, errAlreadyLogin, strlen(errAlreadyLogin));
        redisLog(REDIS_VERBOSE,"%s , you have already login\r\n",c->argv[2]->ptr);
        c->isvaliduser=0;
        c->isvalidnode=0;
        return;
    }

    c->isvaliduser=1;
    c->isvalidnode=1;
    c->mynode_type=MYNODE_TYPE_USER;

    chatSetOrGetUserInfo(c->argv[CHAT_LOGIN_NAME]->ptr,"on",OPERATION_SET_INFO);

    sprintf(c->username,"%s",c->argv[CHAT_LOGIN_NAME]->ptr);
    sprintf(c->password,"%s",c->argv[CHAT_LOGIN_PASSWORD]->ptr);

    char * hostname =getHostNameByName(c);
    redisLog(REDIS_VERBOSE,"hostname is  %s\r\n",hostname);
    sprintf(c->hostname,"%s",hostname);

    
    sprintf(buf,"login ok  %s\r\n",getUseridByName(c));
    addReplyString(c,buf,strlen(buf));
     _chatSend("userinfo",c,c->argv[CHAT_LOGIN_NAME]->ptr,SEND_MESSAGE_TO_FAMILY,"on",MYNODE_TYPE_USER,"NULL","0");
    getAllNodeInfo(c);
    chatUserInfo(c);
    //printf("login success , c->username is %s and c->password is %s \r\n",c->username,c->password);
    return;
}

void nodeLogin(redisClient *c)
{
    char *username=NULL;
    char *hostname=NULL;
    char *userid=NULL;
    char *nodename=NULL;
    char buf[256]={0x00};
    char cmd[256]={0x00};
    char state[256]={0x00};
    int  nodesize=0;
    redisLog(REDIS_VERBOSE,"node  Login %s  %s \r\n",c->argv[2]->ptr,c->argv[3]->ptr);

// modiefied by yongming.li for invalid client
    if(c->isvaliduser  || c->isvalidnode) {
		addReplyString(c, errAlreadyLogin, strlen(errAlreadyLogin));
		return;
    	}

    userid=c->argv[NODE_LOGIN_USERID]->ptr;
    nodename=c->argv[NODE_LOGIN_NAME]->ptr;
    username=getNameByUserid(userid);
    sprintf(c->username,"%s",username);

    redisLog(REDIS_VERBOSE,"username is %s  \r\n",username);

    hostname=getHostNameByName(c);
    redisLog(REDIS_VERBOSE,"hostname is %s  \r\n",hostname);
   
    if (hostname==NULL) {
        addReplyString(c, errWrongNameOrPwd, strlen(errWrongNameOrPwd));
        c->isvaliduser=0;
        c->isvalidnode=0;
        return;
    }

    nodesize=getUserNodeSize(hostname);
    redisLog(REDIS_VERBOSE,"nodesize is %d \r\n",nodesize);

    chatSetOrGetNodeInfo(c->hostname,c->nodename,state,OPERATION_GET_INFO);
    if (!strcmp(state,"on")) {
        addReplyString(c, errAlreadyLogin, strlen(errAlreadyLogin));
        redisLog(REDIS_VERBOSE,"%s, you have already login\r\n", c->argv[2]->ptr);
        c->isvaliduser=0;
        c->isvalidnode=0;
        return;
    }

    int retInsertNode = insertNodeToUserInfo(hostname,nodename);
    if(retInsertNode== (-1)) {
        addReplyString(c, errTooManyNodes, strlen(errTooManyNodes));
        c->isvaliduser=0;
        c->isvalidnode=0;
        return;
    } else if(retInsertNode==1) {
        // modified by yongming.li for mysql table change
        sprintf(cmd,"insert into node (userid,nodeid,command,value)values('%s', '%s',  '0','0');",userid,nodename);
        mysqlRunCommand(cmd);
    }

    sprintf(buf,"login ok %s\r\n",hostname);
    addReplyString(c,buf,strlen(buf));
    c->isvaliduser=1;
    c->isvalidnode=1;
    c->mynode_type=MYNODE_TYPE_NODE;

    sprintf(c->username,"%s",hostname);
    sprintf(c->userid,"%s",userid);
    sprintf(c->nodename,"%s",nodename);
    sprintf(c->hostname,"%s",hostname);
    
    _chatSend("nodeinfo",c,c->nodename,SEND_MESSAGE_TO_FAMILY,"on",MYNODE_TYPE_USER,"NULL","0");

    chatSetOrGetNodeInfo(c->hostname,c->nodename,"on",OPERATION_SET_INFO);

    return;
}

//  node login 3ee50503b2cd6e8ac0ebfc486054f8ee tv
//  node say   self  message
//  node say   tv  message


void nodeSay(redisClient *c)
{
     char * message =c->argv[CHAT_SAY_MESSAGE]->ptr;
     
    if(c->mynode_type==MYNODE_TYPE_USER) 
    {
        _chatSend("node",c,c->username,c->argv[NODE_SAY_NAME]->ptr,message,MYNODE_TYPE_NODE,c->argv[CHAT_SAY_MESSAGEID]->ptr,c->argv[CHAT_SAY_QOS]->ptr);
    } 
    
    if(c->mynode_type==MYNODE_TYPE_NODE) 
    {
    	
         _chatSend("node",c,c->nodename, c->argv[NODE_SAY_NAME]->ptr,message,MYNODE_TYPE_USER,c->argv[CHAT_SAY_MESSAGEID]->ptr,c->argv[CHAT_SAY_QOS]->ptr);
    }
    return;
}

void nodeCommand(redisClient *c)
{
    if(!strcmp(c->argv[NODE_LOGIN_CMD]->ptr,"login")) {
        nodeLogin(c);
        return;
    }

    if(!(c->isvalidnode)) {
        addReplyString(c, errNodeNoLogin, strlen(errNodeNoLogin));
        return;
    }

    /////////////////////////////////////////////////////////////////////
    if(!strcmp(c->argv[NODE_LOGIN_CMD]->ptr,"say")) {
        nodeSay(c);
        return;
    } else if(!strcmp(c->argv[NODE_LOGIN_CMD]->ptr,"heartbeat")) {
        // added by yongming.li for update lastinteraction time
        c->lastinteraction = server.unixtime;
        addReplyString(c, responseHeartBeat, strlen(responseHeartBeat));
        return;
    }

    return;
}

void userCommand(redisClient *c)
{
    if(!strcmp(c->argv[CHAT_LOGIN_CMD]->ptr,"login")) {
        chatLogin(c);
        return;
    } 

     if(!(c->isvaliduser)) {
        addReplyString(c, errUserNoLogin, strlen(errUserNoLogin));
        return;
    }
	
    if(!strcmp(c->argv[CHAT_LOGIN_CMD]->ptr,"say")) {
        chatSay(c);
        return;
    } else if(!strcmp(c->argv[CHAT_LOGIN_CMD]->ptr,"userinfo")) {
        chatUserInfo(c);
        return;
    } else if(!strcmp(c->argv[CHAT_LOGIN_CMD]->ptr,"heartbeat")) {
        // added by yongming.li for update lastinteraction time
        c->lastinteraction = server.unixtime;
        addReplyString(c, responseHeartBeat, strlen(responseHeartBeat));
        return;
    } else if(!strcmp(c->argv[CHAT_LOGIN_CMD]->ptr,"debug")) {
        myDebugEntry(c);
        return;
    } else if(!strcmp(c->argv[CHAT_LOGIN_CMD]->ptr,"adduser")) {
        myAddUser(c);
        return;
    }

    // addReplyError(c,"chat  , sorry , invalid  command ( now only support : say logo regisgter)");
    return;
}
