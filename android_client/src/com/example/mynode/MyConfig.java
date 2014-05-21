package com.example.mynode;

import java.lang.String;

public final class MyConfig {
     public static final int SERVER_PORT = 6379;
     public static final String SERVER_IP = "115.29.235.211";
     public static MyClient  myClient = new MyClient();
     public static MyHeartBeat  myHeartBeat = new MyHeartBeat();
     
     
     public  static final int MSG_SUCCESS = 0;
     public  static final int MSG_FAILURE = 1;
     
     public  static final int MSG_LOGIN_SUCCESS = 10;
     public  static final int MSG_LOGIN_FAILURE = 11;
     public  static final int MSG_LOGIN_USERID = 12;
     
     public  static final int MSG_USER_NODE_INFO_UPDATE = 20;
     
     public  static final int MSG_CHAT_UPDATE = 30;

     
     public static final int  PROTOCOL_CODE_DO_NOTHING= 999;
     public static final int  PROTOCOL_CODE_LOGIN= 0;
     public static final int  PROTOCOL_CODE_ALLUSER= 1;
     public static final int  PROTOCOL_CODE_CHAT = 2;
     public static int   PROTOCOL_CODE = PROTOCOL_CODE_LOGIN;
}
