#ifndef __MY_USER_H
#define __MY_USER_H

#define  MYNODE_ARRAY_SEARCH_USER  0
#define  MYNODE_DICT_SEARCH_USER  1


#define  MY_NAME_LENGTH  256

extern void myuser_init();

extern void   insertUserInfo(char * userid , char * name);
extern int    insertNodeToUserInfo(char * username , char * nodename);
extern int    getUserNodeSize(char * username );
extern void   chatUserInfo(redisClient *c);
extern void   getAllNodeInfo(redisClient *c );
extern char *   getUseridByName(redisClient *c);
extern char *   getNameByUserid(char * userid);
extern void   chatUpdateUserInfo(char * username,char * state);
extern void   chatUpdateNodeInfo(char * username,char * nodename,char * state);


extern void   chatSetOrGetNodeInfo(char * username,char * nodename,char * state, int operation);
extern void   chatSetOrGetUserInfo(char * username,char * state,int operation);

#endif
