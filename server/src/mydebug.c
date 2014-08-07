// this file added by yongming.li for node data

#include "redis.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>  
#include <unistd.h>  
#include <sys/types.h>  
#include <sys/ipc.h>  
#include <sys/stat.h>  
#include <sys/msg.h> 

#include "mydump.h"
#include "credis.h"
#include "mychat.h"
#include "myuser.h"
#include "mydebug.h"

void dumpClients(redisClient *c)
{
    int i=0;
    char buf[256]={0x00};
    int numclients = listLength(server.clients);
    redisClient * ctemp;
    listNode * head;
    sprintf(buf," total %-6d client on line\r\n",numclients);
    addReplyString(c,buf,strlen(buf));
    //redisLog(REDIS_NOTICE,"numclients is %d \r\n",numclients);
    while(i++<numclients) {
        listRotate(server.clients);
        head = listFirst(server.clients);
        ctemp = listNodeValue(head);
        if(ctemp==NULL)
        { 
           redisLog(REDIS_NOTICE,"i  is %d and c == NULL \r\n",i);
           break;
        }
        // modified by yongming.li for use redisLog instead of printf for easy to debug
        sprintf(buf,"type:%-5d  name :%-15s id:%-40s nodename:%-15s \r\n",ctemp->mynode_type,ctemp->username,ctemp->userid,ctemp->nodename);
        addReplyString(c,buf,strlen(buf));
        // redisLog(REDIS_NOTICE,"client :%-15s id:-30%s nodename:%-15s  type:%-5d\r\n",c->username,c->userid,c->nodename,c->mynode_type);
    }
}

int dumpAlluser(redisClient *c) {
    dictIterator *di = dictGetSafeIterator(myuserdict);
    dictEntry *de;
    int count = 0;
    char buf[256]={0x00};
    
    while((de = dictNext(di)) != NULL) {
        MyNodeUserInfo * nodeuseinfo  = dictGetVal(de);
        sprintf(buf,"username : %-25s and userid : %-25s  and   line :%-5s\r\n ",nodeuseinfo->name,nodeuseinfo->userid,nodeuseinfo->line);
        #if 0
        if(nodeuseinfo->index==0)
        	{
        	     continue;
        	}
        #endif
        
        if(strcmp(nodeuseinfo->name,nodeuseinfo->hostname))
        	{
        	      continue;
        	}
        
        addReplyString(c,buf,strlen(buf));

        MyNodeUserInfo * nodeuseinfoTemp=nodeuseinfo->nextfamily;
         while(nodeuseinfoTemp)
        	{
        	    sprintf(buf," -----username : %-25s and userid : %-25s  and   line :%-5s\r\n  ",nodeuseinfoTemp->name,nodeuseinfoTemp->userid,nodeuseinfoTemp->line);
        	    addReplyString(c,buf,strlen(buf));
        	    nodeuseinfoTemp=nodeuseinfoTemp->nextfamily;
        	}

        int nodeIndex =nodeuseinfo->index;
        for(int j=0;j<nodeIndex;j++)
        {
              sprintf(buf,"----------nodename : %-20s  line :%-5s\r\n",nodeuseinfo->nodes[j].name,nodeuseinfo->nodes[j].line);
              //redisLog(REDIS_NOTICE,buf);
              addReplyString(c,buf,strlen(buf));
              
        }
    }
    dictReleaseIterator(di);
    return count;
}
void  myDebugEntry(redisClient *c)
{
      if(strcmp(c->username,MY_REDIS_ROOT_NAME))
      {
      	     return;
      }
      //dumpClients(c);
      dumpAlluser(c);
      return;
}

//  user  login root root  r  r 
//  user  adduser    userid  username  hostname  isHost
//  e:  user adduser  45454545effdf   yongming  yongming       yes
//  e:  user adduser  45454545effdf   yongming  yongmingson  no
void  myAddUser(redisClient *c)
{
      if(strcmp(c->username,MY_REDIS_ROOT_NAME))
      {
            addReplyString(c, "not_root", strlen("not_root"));
      	     return;
      }
      unsigned char isHost =0;
      if (!strcmp(c->argv[5]->ptr,"yes"))
      {
      	     isHost=1;
      }
      //void   insertUserInfo(char * userid , char * username ,char * hostname ,  unsigned char isHost);
      insertUserInfo(c->argv[2]->ptr , c->argv[3]->ptr,c->argv[4]->ptr,isHost);
      addReplyString(c, "user adduser ok", strlen("user adduser ok"));
      return;
}


