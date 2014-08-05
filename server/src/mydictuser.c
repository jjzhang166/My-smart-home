// this file added by yongming.li for user data


#include "redis.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "credis.h"
#include "myuser.h"
#include "mydump.h"
#include "mychat.h"
#include "dict.h"


//  avoid memory leak
#if 0
struct redisCommand *lookupCommandByCString(char *s) {
    struct redisCommand *cmd;
    sds name = sdsnew(s);

    cmd = dictFetchValue(server.commands, name);
    sdsfree(name);
    return cmd;
}
#endif

#if   MYNODE_DICT_SEARCH_USER

extern dict * myuserdict;

void  myuser_init()
{
      // do nothing now
}



MyAllNodeUserInfo myAllNodeUserInfo={NULL,0};

struct _MyNodeUserInfo * newMyNodeUserInfo()
{
      MyNodeUserInfo * nodeuseinfo= zmalloc(sizeof(MyNodeUserInfo));
      nodeuseinfo->next=NULL;
      nodeuseinfo->index=0;
      nodeuseinfo->nextfamily=NULL;
      memset(nodeuseinfo->name,0X00,MY_NAME_LENGTH);
      memset(nodeuseinfo->userid,0X00,MY_NAME_LENGTH);
      memset(nodeuseinfo->hostname,0X00,MY_NAME_LENGTH);
      
      memset(nodeuseinfo->line,0X00,MY_NAME_LENGTH);

      return nodeuseinfo;
}

// modified interface by yongming.li
void   insertUserInfo(char * userid , char * username ,char * hostname ,  unsigned char isHost)
{
    MyNodeUserInfo * nodeuseinfo = NULL;
    sds nameTemp = sdsnew(username);
    nodeuseinfo = dictFetchValue(myuserdict, nameTemp);
    sdsfree(nameTemp);
    if(nodeuseinfo!=NULL)
    {
          if(isHost)
          	{
          	   return ;
          	}
    	     
    }

    nodeuseinfo = newMyNodeUserInfo();
    MyNodeUserInfo * tempnodeuseinfo = myAllNodeUserInfo.userInfo;
    strcpy(nodeuseinfo->name,username);
    strcpy(nodeuseinfo->userid,userid);
    strcpy(nodeuseinfo->hostname,hostname);
    redisLog(REDIS_VERBOSE,"insert hostname is %s and username is  %s \r\n",hostname,nodeuseinfo->hostname);
    strcpy(nodeuseinfo->line,"off");
    nodeuseinfo->index=0;

    dictAdd(myuserdict, sdsnew(username),nodeuseinfo);

    myAllNodeUserInfo.index=myAllNodeUserInfo.index+1;
    myAllNodeUserInfo.userInfo=nodeuseinfo;
    nodeuseinfo->next = tempnodeuseinfo;

    if(!isHost)
    {
              redisLog(REDIS_VERBOSE,"insertUserInfo  is not host \n");
              MyNodeUserInfo * nodeuseinfoHost = NULL;
              nameTemp = sdsnew(hostname);
              nodeuseinfoHost = dictFetchValue(myuserdict, nameTemp);
              sdsfree(nameTemp);
              if(nodeuseinfoHost==NULL)
             {
    	            return ;
             }
             redisLog(REDIS_VERBOSE,"insertUserInfo  added to list \n");
             tempnodeuseinfo = nodeuseinfoHost->nextfamily;
             nodeuseinfoHost->nextfamily=nodeuseinfo;
             nodeuseinfo->nextfamily=tempnodeuseinfo;
    }
    return;
}


//   1 : means a new node
//   0 : means has exits
int    insertNodeToUserInfo(char * username , char * nodename)
{

    MyNodeUserInfo * nodeuseinfo = NULL;
    sds name = sdsnew(username);
    nodeuseinfo = dictFetchValue(myuserdict, name);
    sdsfree(name);
    if(nodeuseinfo==NULL)
    	{
    	     return -2;
    	}

          int nodeIndex =nodeuseinfo->index;
          for(int j=0;j<nodeIndex;j++)
         {
                 if(!strcmp(nodename,nodeuseinfo->nodes[j].name))
                {
                      return 0;
                }
         }
         if(nodeuseinfo->index>=MYNODE_MAX_NODES)
        {
              return -1;
        }
        strcpy(nodeuseinfo->nodes[nodeIndex].name,nodename);
        strcpy(nodeuseinfo->nodes[nodeIndex].line,"off");
        nodeuseinfo->index=nodeIndex+1;
        printf("insertNodeToUserInfo  %s  %s  index is %d\r\n",username,nodename,nodeuseinfo->index);
        return 1;

}

int    getUserNodeSize(char * username )
{

    MyNodeUserInfo * nodeuseinfo = NULL;
    sds name = sdsnew(username);
    nodeuseinfo = dictFetchValue(myuserdict, name);
    sdsfree(name);
    if(nodeuseinfo==NULL)
    {
    	     return 0;
    }
    return  nodeuseinfo->index;
}


void   chatUserInfo(redisClient *c)
{

    char buf[256]={0x00};
    MyNodeUserInfo * nodeuseinfo = NULL;

    #if 0
    for(nodeuseinfo=myAllNodeUserInfo.userInfo;nodeuseinfo!=NULL;nodeuseinfo=nodeuseinfo->next)
    {
         sprintf(buf,"userinfo ok %s %s\r\n",nodeuseinfo->name,nodeuseinfo->line);
         addReplyString(c,buf,strlen(buf));
    }
    #endif
    
    sds name = sdsnew(c->hostname);
    nodeuseinfo = dictFetchValue(myuserdict, name);
    sdsfree(name);
    if(nodeuseinfo==NULL)
    {
    	     return ;
    }
    sprintf(buf,"userinfo ok %s %s NULL 0\r\n",nodeuseinfo->name,nodeuseinfo->line);
    addReplyString(c,buf,strlen(buf));
    MyNodeUserInfo * nodeuseinfoTemp=nodeuseinfo->nextfamily;
    while(nodeuseinfoTemp)
    {
        	sprintf(buf,"userinfo ok %s %s NULL 0\r\n",nodeuseinfoTemp->name,nodeuseinfoTemp->line);
         addReplyString(c,buf,strlen(buf));
         nodeuseinfoTemp=nodeuseinfoTemp->nextfamily;
     }
    return;
}

void   getAllNodeInfo(redisClient *c )
{
    char buf[256]={0x00};



    MyNodeUserInfo * nodeuseinfo = NULL;
    sds name = sdsnew(c->hostname);
    nodeuseinfo = dictFetchValue(myuserdict, name);
    sdsfree(name);
    if(nodeuseinfo==NULL)
    	{
    	     return ;
    	}

        int nodeIndex =nodeuseinfo->index;
        for(int j=0;j<nodeIndex;j++)
       {
              sprintf(buf,"nodeinfo ok %s %s NULL 0\r\n",nodeuseinfo->nodes[j].name,nodeuseinfo->nodes[j].line);
              addReplyString(c,buf,strlen(buf));
       }


}

char *   getUseridByName(redisClient *c)
{
    MyNodeUserInfo * nodeuseinfo = NULL;
    sds name = sdsnew(c->username);
    nodeuseinfo = dictFetchValue(myuserdict, name);
    sdsfree(name);
    if(nodeuseinfo==NULL)
    {
    	     return NULL;
    }
    return  nodeuseinfo->userid;
}

char *   getHostNameByName(redisClient *c)
{
    MyNodeUserInfo * nodeuseinfo = NULL;
    sds name = sdsnew(c->username);
    nodeuseinfo = dictFetchValue(myuserdict, name);
    sdsfree(name);
    if(nodeuseinfo==NULL)
    {
    	     return NULL;
    }
    return  nodeuseinfo->hostname;
}


char *   getNameByUserid(char * userid)
{
    MyNodeUserInfo * nodeuseinfo = NULL;
    for(nodeuseinfo=myAllNodeUserInfo.userInfo;nodeuseinfo!=NULL;nodeuseinfo=nodeuseinfo->next)
    {
     if(!strcmp(userid,nodeuseinfo->userid))
			        {
			             return nodeuseinfo->name;
			        }
		 }
	  return NULL;
}


void   chatSetOrGetUserInfo(char * username,char * state,int operation)
{
    MyNodeUserInfo * nodeuseinfo = NULL;
    sds name = sdsnew(username);
    nodeuseinfo = dictFetchValue(myuserdict, name);
    sdsfree(name);
    if(nodeuseinfo==NULL)
    	{
    	     return ;
    	}
     if(operation==OPERATION_GET_INFO)
     	{
     	     strcpy(state,nodeuseinfo->line);
     	}
     if(operation==OPERATION_SET_INFO)
     	{
     	     strcpy(nodeuseinfo->line,state);
     	}

     return;
}

void   chatSetOrGetNodeInfo(char * username,char * nodename,char * state, int operation)
{
    MyNodeUserInfo * nodeuseinfo = NULL;
    sds name = sdsnew(username);
    nodeuseinfo = dictFetchValue(myuserdict, name);
    sdsfree(name);
    if(nodeuseinfo==NULL)
    	{
    	     return ;
    	}
      int nodeIndex =nodeuseinfo->index;
      for(int j=0;j<nodeIndex;j++)
     {
             if(!strcmp(nodename,nodeuseinfo->nodes[j].name))
            {

                    if(operation==OPERATION_GET_INFO)
								     	{
								     	     sprintf(state,"%s",nodeuseinfo->nodes[j].line);
								     	}
								     if(operation==OPERATION_SET_INFO)
								     	{
								     	     sprintf(nodeuseinfo->nodes[j].line,"%s",state);
								     	}
                  return ;
            }
     }
    return;
}

#endif


