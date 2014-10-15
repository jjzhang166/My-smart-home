// this file added by yongming.li for node data

#include "redis.h"

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

#include<mysql/mysql.h>

#include "credis.h"
// -lmysqlclient  for gcc

#define REDIS_THREAD_STACK_SIZE (1024*1024*4)

MYSQL my_mysql_query;


int insert_all_node(char * userid,char * username)
{
     MYSQL mysql;
     MYSQL_RES *res;
     MYSQL_ROW row;
     int t;

     char query[256] ={0x00} ;
     char buf[256]={0x00};

     //mysql_query("CREATE  TABLE node  (userid VARCHAR(50) ,nodeid VARCHAR(50),command VARCHAR(50) , value VARCHAR(50))",$con);
     sprintf(query,"select  nodeid  from node where userid='%s' ;",userid);
     //redisLog(REDIS_VERBOSE,"query is %s \r\n",query);


     mysql_init(&mysql);
     if(!mysql_real_connect(&mysql,"localhost","root",
                     "123456","mynode",0,NULL,0))
     {
         redisLog(REDIS_VERBOSE,"Error connecting to database:%s\n",mysql_error(&mysql));
         return -1;
     }

      t=mysql_query(&mysql,query);
     if(t)
     {
         redisLog(REDIS_VERBOSE,"Error making query:%s\n",mysql_error(&mysql));
     }
     else
     {

         res = mysql_use_result(&mysql);
         while (row = mysql_fetch_row(res))
         {
               sprintf(buf,"%s",row[0]);
               insertNodeToUserInfo(username,row[0]);
         }

         mysql_free_result(res);
     }
     mysql_close(&mysql);

}

int insert_all_family(char * userid,char * hostname)
{
     MYSQL mysql;
     MYSQL_RES *res;
     MYSQL_ROW row;
     int t;

     char query[256] ={0x00} ;
     char buf[256]={0x00};

     sprintf(query,"select  name  from user where hostname='%s'  and  host=0;",hostname);
     redisLog(REDIS_VERBOSE,"family query is %s \r\n",query);


     mysql_init(&mysql);
     if(!mysql_real_connect(&mysql,"localhost","root",
                     "123456","mynode",0,NULL,0))
     {
         redisLog(REDIS_VERBOSE,"Error connecting to database:%s\n",mysql_error(&mysql));
         return -1;
     }
      t=mysql_query(&mysql,query);
     if(t)
     {
         redisLog(REDIS_VERBOSE,"Error making query:%s\n",mysql_error(&mysql));
     }
     else
     {
         res = mysql_use_result(&mysql);
         while (row = mysql_fetch_row(res))
         {

                sprintf(buf,"%s",row[0]);
                //redisLog(REDIS_VERBOSE,"family query name is  %s \r\n",buf);
                insertUserInfo(userid,row[0],hostname,0);
         }

         mysql_free_result(res);
     }
     mysql_close(&mysql);

}

int do_mysql_dump_redis(void *arg)
{

     MYSQL_RES *res;
     MYSQL_ROW row;
     MYSQL mysql;
     int t,r;
     int i=0;
     char query[256] ={0x00} ;
     char hostname[256]={0x00};
     char userid[256]={0x00};




     mysql_init(&mysql);
     if(!mysql_real_connect(&mysql,"localhost","root",
                     "123456","mynode",0,NULL,0))
     {
         redisLog(REDIS_VERBOSE,"Error connecting to database:%s\n",mysql_error(&mysql));
     }
     else
         redisLog(REDIS_VERBOSE,"Connected........");

    // modiefid by yongming.li for family

     sprintf(query,"select  userid,name,password  from user  where host=1;");
     redisLog(REDIS_VERBOSE,"main query is %s \r\n",query);
     t=mysql_query(&mysql,query);
     if(t)
     {
         redisLog(REDIS_VERBOSE,"Error making query:%s\n",mysql_error(&mysql));
     }
     else
     {
         res = mysql_use_result(&mysql);

         while (row = mysql_fetch_row(res))
         {
               // this is host
               sprintf(hostname,"%s",row[1]);
               sprintf(userid,"%s",row[0]);

               redisLog(REDIS_VERBOSE,"userid  is  %s and hostname is %s \r\n",userid,hostname);

               insertUserInfo(userid,hostname,hostname,1);
               insert_all_node(userid,hostname);
               // this is family members
               insert_all_family(userid,hostname);
               i++;
         }
         mysql_free_result(res);
     }
      mysql_close(&mysql);

      #if 0
      char temp_id[256]="454545454545";
      char temp_name[256]="fuck";
      char temp_name_family[256]="fuckson";
      char temp_name_node[256]="fdsjklj";
      insertUserInfo(temp_id , temp_name,temp_name,1);
      insertNodeToUserInfo(temp_name,temp_name_node);
      insertUserInfo(temp_id, temp_name_family,temp_name,0);
      #endif

     return 0;
 }


int mysql_query_init()
{

     mysql_init(&my_mysql_query);
     mysql_real_connect(&my_mysql_query,"localhost","root",
                     "123456","mynode",0,NULL,0);

 }

int is_valid_user(char * name ,char * password)
{
     MYSQL mysql;
     MYSQL_RES *res;
     MYSQL_ROW row;
     int t;

     char query[256] = {0x00};

     sprintf(query,"select  name  from user where name='%s' and password='%s' ;",name,password);
     redisLog(REDIS_VERBOSE,"query is %s \r\n",query);


     mysql_init(&mysql);
     mysql_real_connect(&mysql,"localhost","root","123456","mynode",0,NULL,0);
     t=mysql_query(&mysql,query);
     if(t)
     {
         redisLog(REDIS_VERBOSE,"Error making query:%s\n",mysql_error(&mysql));
     }
     else
     {
         res = mysql_use_result(&mysql);
         if(row = mysql_fetch_row(res))
         {
             redisLog(REDIS_VERBOSE,"mysql :  %s logon  is successful \n",name);
             mysql_free_result(res);
             mysql_close(&mysql);
             return 1;
         }
         else
         {
            redisLog(REDIS_VERBOSE,"mysql : %s logon is failed\n",name);

         }
          mysql_free_result(res);
     	}
     mysql_close(&mysql);
     return 0;
}

//  1 means exist
int  mysql_is_exist(char * cmd)
{
      int t,r;
      MYSQL_RES *res;
      MYSQL_ROW row;

      redisLog(REDIS_VERBOSE,"cmd is %s \r\n",cmd);
      mysql_query(&my_mysql_query,cmd);
      if(t)
     {
         redisLog(REDIS_VERBOSE,"Error making query:%s\n",mysql_error(&my_mysql_query));
         return 1;
     }
     else
     {
         res = mysql_use_result(&my_mysql_query);
         if(row = mysql_fetch_row(res))
         {
             mysql_free_result(res);
             return 1;
         }
         else
         {
             mysql_free_result(res);
             return 0;
         }
     	}
}

void  mysqlRunCommand(char * cmd)
{
     if(cmd==NULL)
     	{
     	    return;
     	}
     redisLog(REDIS_VERBOSE,"cmd is %s \r\n",cmd);
     mysql_query(&my_mysql_query,cmd);
     return ;
}




int mysql_dump_to_memory()
{
    pthread_t thread;
    pthread_attr_t attr;
    size_t stacksize;

    /* Set the stack size as by default it may be small in some system */
    pthread_attr_init(&attr);
    pthread_attr_getstacksize(&attr,&stacksize);
    if (!stacksize) stacksize = 1; /* The world is full of Solaris Fixes */
    while (stacksize < REDIS_THREAD_STACK_SIZE) stacksize *= 2;
    pthread_attr_setstacksize(&attr, stacksize);
    pthread_create(&thread,&attr,do_mysql_dump_redis,NULL);

    mysql_query_init();

  return 0;
}

