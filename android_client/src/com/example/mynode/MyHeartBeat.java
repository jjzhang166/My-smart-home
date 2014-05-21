package com.example.mynode;

import android.util.Log;

public class MyHeartBeat {
	
	private static final String TAG = "MyHeartBeat";
	
	public void start() throws InterruptedException 
	{
		while(true)
		{
			try {
				Log.e(TAG, "send heartbeat again"); 
				MyConfig.myClient.runCmd("chat heartbeat 0 0");
				Thread.sleep(45*1000);
			} catch (Exception e) {
				Log.e(TAG, "start  : "+e.toString());  
			}
		}
	}
}
