// this file added by yongming.li for node data

#include "redis.h"
#include <math.h>

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "mynode.h"
#include <stdlib.h>

#include <errno.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/ipc.h>  
#include <sys/stat.h>  
#include <sys/msg.h> 

#include<mysql/mysql.h>
#include "credis.h"


// -lmysqlclient  for gcc 
// yongming.li for command sync

//  if ((o = hashTypeLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
#if 0
int  isExist(,)
{
    robj *hashTypeLookupWriteOrCreate(redisClient *c, robj *key) {
    	
	    robj *o = lookupKeyWrite(c->db,key);
	    if (o == NULL) {
	        o = createHashObject();
	        dbAdd(c->db,key,o);
	    } else {
	        if (o->type != REDIS_HASH) {
	            addReply(c,shared.wrongtypeerr);
	            return NULL;
	        }
	    }
	    return o;
   }
}
#endif 

void mychat_reply(redisClient *c,char * str)
{
   char buf[256]={0x00};
   sprintf(buf,"+%s\r\n",str);
   addReplyString(c,buf,strlen(buf));
   return;
}

int  getUserinfo(redisClient *c,robj *field) {
    robj *o;
    int ret;
    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.nullbulk)) == NULL ||
        checkType(c,o,REDIS_HASH)) return;

    addHashFieldToReply(c, o, c->argv[2]);

    if (o == NULL) {
        addReply(c, shared.nullbulk);
        return 0;
    }
    //addHashFieldToReply(c, o, c->argv[2]);
    //static void addHashFieldToReply(redisClient *c, robj *o, robj *field) 
    
    printf("o->encoding  is %d \r\n",o->encoding);
    if (o->encoding == REDIS_ENCODING_ZIPLIST) {
        unsigned char *vstr = NULL;
        unsigned int vlen = UINT_MAX;
        long long vll = LLONG_MAX;

        ret = hashTypeGetFromZiplist(o, field, &vstr, &vlen, &vll);
        if (ret < 0) {
            addReply(c, shared.nullbulk);
        } else {
            if (vstr) {
                addReplyBulkCBuffer(c, vstr, vlen);
            } else {
                addReplyBulkLongLong(c, vll);
            }
        }

    } else if (o->encoding == REDIS_ENCODING_HT) {
        robj *value;

        ret = hashTypeGetFromHashTable(o, field, &value);
        if (ret < 0) {
            addReply(c, shared.nullbulk);
        } else {
            addReplyBulk(c, value);
            printf("value   is %s \r\n",value->ptr);
        }

    } else {
        redisPanic("Unknown hash encoding");
    }
}
void sendtoclient(redisClient *c)
{

    int numclients = listLength(server.clients);
    redisClient *ctemp;
    listNode *head;
    int i=0;
    int  slen;
    char sbuf[128];
    
    while(i++<numclients) {
    	   listRotate(server.clients);
        head = listFirst(server.clients);
        ctemp = listNodeValue(head);
        if(ctemp==NULL)
        { 
           break;
        }
        printf("userid is %s  and nodeid is %s \r\n",ctemp->userid,ctemp->nodeid);
         if (!strcmp(ctemp->userid,MY_REDIS_ROOT_NAME) )
        	{
        	   continue;
        	}
        if (strcmp(ctemp->nodeid,c->argv[1]->ptr) )
        	{
        	   continue;
        	}

        slen = snprintf(sbuf,sizeof(sbuf),"$%d\r\n%s\r\n",strlen(c->argv[3]->ptr),c->argv[3]->ptr);
        addReplyString(ctemp,sbuf,slen);
         break;
    }
   
}

void chat_sendtoclient(redisClient *c , char * from , char * to ,char * message)
{

    int numclients = listLength(server.clients);
    redisClient *ctemp;
    listNode *head;
    int i=0; 
    int  slen;
    char sbuf[128];
    char sbuftemp[128];
    
    while(i++<numclients) {
    	   listRotate(server.clients);
        head = listFirst(server.clients);
        ctemp = listNodeValue(head);
        if(ctemp==NULL)
        { 
           break;
        }
        printf("ctemp->username is %s   \r\n",ctemp->username);
         if (strcmp(to,"all")  &&  strcmp(ctemp->username,to)   )
        	{
        	   continue;
        	}
         if (!strcmp(ctemp->userid,MY_REDIS_ROOT_NAME) )
        	{
        	   continue;
        	}
        slen = snprintf(sbuftemp,sizeof(sbuftemp),"%s:%s",from,message);
        printf("sbuftemp is %s   \r\n",sbuftemp);
        slen = snprintf(sbuf,sizeof(sbuf),"$%d\r\n%s\r\n",slen,sbuftemp);
        printf("sbufis %s   \r\n",sbuf);
        addReplyString(ctemp,sbuf,slen);
        //break;
    }
    
}
int   logonCommand(redisClient *c)
{
    if(strcmp(c->argv[2]->ptr,"value") &&  strcmp(c->argv[2]->ptr,"command") )
     {
         addReplyError(c,"hsetCommand , sorry , only support : value  / command");
         c->isvaliduser=0;
         return -1;
     }
      c->isvaliduser=1;
      return 0;
}


//  chat   "somebody"   "message"
//  chat   register  name password
//  chat   logon  name userword
//  chat   say   otherbodyname  messagebody

int chat_sismember(redisClient *c) {
    robj *set;

    if ((set = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL)
    	{
    	    return 0;
    	}
        
    c->argv[2] = tryObjectEncoding(c->argv[2]);
    printf("c->argv[2]->ptr is %s \r\n",c->argv[2]->ptr);
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
        addReplyError(c,"chat ,please logon first");
        return;
    }
    //robj * o = createObject(REDIS_STRING,sdsnew("alluser"));
    //sprintf(c->argv[1]->ptr,"%s","alluser");                                                
    //printf("c->argv[1]->ptr is %s \r\n",c->argv[1]->ptr);
    #if 0
    if(!chat_sismember(c))
    {
        addReplyError(c,"chat,sorry,no such user");
    }
    #endif 
    chat_sendtoclient(c,c->username,c->argv[2]->ptr,c->argv[3]->ptr);
    return;
}
void chatLogon(redisClient *c)
{
    int ret =0;
    ret=is_valid_user(c->argv[2]->ptr,c->argv[3]->ptr);
    if(ret<=0)
    {
    	    //addReplyError(c,"chat  , sorry , wrong username or password ,please check carefully");
    	    mychat_reply(c,"fail");
    	    c->isvaliduser=0;
    	    return;
    	    
    }
    c->isvaliduser=1;
    mychat_reply(c,"ok");
    sprintf(c->username,"%s",c->argv[2]->ptr);
    sprintf(c->password,"%s",c->argv[3]->ptr);
    printf("logon success , c->username is %s and c->password is %s \r\n",c->username,c->password);
    return;
}
void chatCommand(redisClient *c)
{
     if(!strcmp(c->argv[1]->ptr,"logon"))
     {
     	    chatLogon(c);
     	    return;
     }
     if(!strcmp(c->argv[1]->ptr,"say"))
     {
     	    chatSay(c);
     	    return;
     }
     #if 0
      if(!strcmp(c->argv[1]->ptr,"register"))
     {
     	    chatSay(c);
     	    return;
     }
     #endif 
     addReplyError(c,"chat  , sorry , invalid  command(lnow only support : say logo regisgter)");
     return;
}

