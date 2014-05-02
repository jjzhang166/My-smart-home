package com.example.mynode;

import java.util.ArrayList;
import java.util.HashMap;

import android.app.Activity;
import android.content.Intent;
import android.os.Handler;
import android.util.Log;

public class MyParse  {
	Handler m_handle;
	
	public  static  ArrayList<String> protocolList = new ArrayList<String>();
	
	//public  static  ArrayList<HashMap<String, Object>> userList = new ArrayList<HashMap<String, Object>>();
	
	public  static  HashMap<String, Object> userList = new HashMap<String, Object>();
	
	public  static  HashMap<String, Object> nodeList = new HashMap<String, Object>();
	

	
	private static  int alluserinex=0;
	private static  int allusersize=0;
	
    private static final String ACTION_ALLUSER_UPDATE =
            "com.example.mynode.action.ALLUSER.UPDATE";
    

	public void loginparse()
	{
        //Log.e("LoginParse",line);
        if(protocolList.get(0).startsWith("ok"))
        {
        	m_handle.obtainMessage(MyConfig.MSG_LOGIN_SUCCESS,"ok").sendToTarget();
        	m_handle.obtainMessage(MyConfig.MSG_LOGIN_USERID,protocolList.get(1)).sendToTarget();
            return;
        }

        if(protocolList.get(0).startsWith("fail"))
        {
        	m_handle.obtainMessage(MyConfig.MSG_LOGIN_FAILURE,"fail").sendToTarget();
        	return;
        }
	}
	public void userOrNodeinfoparse(HashMap<String, Object> mylist)
	{
        //Integer.parseInt(line.trim());
		String name=protocolList.get(1);
		String onOffLine=protocolList.get(2);
		HashMap<String, Object> map=null;
		if(mylist.containsKey(name))
		{
			map=(HashMap<String, Object>)mylist.get(name);
			map.put("line",onOffLine);
			return;
		}
		else
		{
			map = new HashMap<String, Object>();
		}
        map.put("name", name);
        map.put("messagesize","0");
        map.put("messages",new ArrayList<String>());
        map.put("line",onOffLine);
        mylist.put(name, map);
        m_handle.obtainMessage(MyConfig.MSG_USER_NODE_INFO_UPDATE,mylist).sendToTarget();		
	}
	// chat ok test shit
	public void chatparse(HashMap<String, Object> mylist) {
		try {

			// String fromwho = (String)protocolList.get(1);
			String name = (String) protocolList.get(1);
			String message = (String) protocolList.get(2);

			if (!mylist.containsKey(name)) {
				return;
			}
			HashMap<String, Object> map = null;
			map = (HashMap<String, Object>) mylist.get(name);

			String messagesize = (String) map.get("messagesize");
			int tempmessagesize = 0;
			tempmessagesize = Integer.parseInt(messagesize) + 1;
			map.put("messagesize", String.format("%d", tempmessagesize));
			ArrayList<String> messageList = (ArrayList<String>) map
					.get("messages");
			messageList.add(message);

			m_handle.obtainMessage(MyConfig.MSG_CHAT_UPDATE,
					name + ":" + message).sendToTarget();

		} catch (Exception e) {
			Log.e("Myparse", e.toString());
		}
		return;
	}

	public void parse(Handler handle, String line) {
		m_handle = handle;
        
		//Log.e("parse",line);
		try {
			/*
			
			String str = "关键词1     关键词2      关键词3";  
			String[] words = str.split("\\s+");  
			for(String word : words){  
			     System.out.println(word);  
			}
			*/
			String strArray[] = line.split("\\s+");
			protocolList.clear();
			for(int i=1 ; i< strArray.length;i++)
			{
				protocolList.add(strArray[i].trim());
				//Log.e("parse",strArray[i].trim());
			}
			if(protocolList.size()==0)
			{
				// do nothing
				return;
			}
			if (line.startsWith("login")) {
				loginparse();
				return;
			}
			if (line.startsWith("userinfo")) {
				userOrNodeinfoparse(userList);
				return;
			}
			if (line.startsWith("nodeinfo")) {
				userOrNodeinfoparse(nodeList);
				return;
			}
			if (line.startsWith("chat")) {
				chatparse(userList);
				return;
			}
			if (line.startsWith("node")) {
				chatparse(nodeList);
				return;
			}
			// do nothing
			
		} catch (Exception e) {
			Log.e("Myparse", e.toString());
		}

	}
	
}
