
package com.example.mynode.chat;

import android.app.Activity;
import android.graphics.Color;
import android.graphics.drawable.GradientDrawable;
import android.graphics.drawable.GradientDrawable.Orientation;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.Window;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.Spinner;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.HashMap;

import com.example.mynode.MyConfig;
import com.example.mynode.MyParse;
import com.example.mynode.MyParseCommon;
import com.example.mynode.R;

public class ChatActivity extends Activity {
    private static final String TAG = ChatActivity.class.getSimpleName();
    private ListView talkView;
    private Button sendButton;
    private EditText messageText;
    private String mRevText;
    private String talkToWho;
    private String chatmode;
    
    private Spinner mMessageSpinner;

    // private ChatMsgViewAdapter myAdapter;

    private ArrayList<ChatMsgEntity> chatlist = new ArrayList<ChatMsgEntity>();
    
    public  static  HashMap<String, Object> userNodeList;
    
    public  static  ArrayList<String> normalMeassgelList = new ArrayList<String>();
    
    static
    {
        normalMeassgelList.add("open");
        normalMeassgelList.add("close");
        normalMeassgelList.add("hello");
    }

    protected void onStart() {  
        // TODO Auto-generated method stub  
        super.onStart();  
        Log.e("ChatActivity", "执行：onStart()");  
        MyConfig.myClient.setHandle(mHandler);
    }  
    public void onCreate(Bundle savedInstanceState) {
        Log.v(TAG, "onCreate >>>>>>");
        super.onCreate(savedInstanceState);
        // added by yongming.li for hide title
        //requestWindowFeature(Window.FEATURE_NO_TITLE);
        setContentView(R.layout.chat_main);
        
        Bundle bundle=getIntent().getExtras();  
        talkToWho=bundle.getString("name"); 
        
        chatmode=bundle.getString("mode");
        if(chatmode.equalsIgnoreCase("node"))
        {
        	//Log.v(TAG, "onCreate node mode >>>>>>");
        	userNodeList=MyParse.nodeList;
        }
        if(chatmode.equalsIgnoreCase("user"))
        {
        	//Log.v(TAG, "onCreate user mode >>>>>>");
        	userNodeList=MyParse.userList;
        }
        setTitle("正在同 "+talkToWho+" 聊天"); 
        talkView = (ListView) findViewById(R.id.ChatList);
        
        

        sendButton = (Button) findViewById(R.id.SendMessageButton);
        messageText = (EditText) findViewById(R.id.ChatMessageText);
        OnClickListener messageButtonListener = new OnClickListener() {

            @Override
            public void onClick(View arg0) {
                // TODO Auto-generated method stub

            	if(arg0==sendButton)
            	{ 
            		String name = getFromwho();
            		String parentname = MyParseCommon.getParentNameByName(userNodeList,name);
            		String str = String.format("chat say %s %s ",parentname,messageText.getText().toString());
            		
                    if(chatmode.equalsIgnoreCase("node"))
                    {
                    	str = String.format("node say %s name=%s,value=%s ",parentname,name,messageText.getText().toString());
                    }
            		Log.e(TAG, str); 	
            		MyConfig.myClient.runCmd(str);
            	    chatUpdate("me");
            	    return;
            	}
            }

        };
        sendButton.setOnClickListener(messageButtonListener);
        sendButton.setFocusable(true);
        
        Log.e("ChatActivity", "userNodeList");
        try
        {
        	if(userNodeList.containsKey(talkToWho))
            {
            	HashMap<String, Object> map = (HashMap<String, Object>)userNodeList.get(talkToWho);
            	ArrayList<String> messageList = (ArrayList<String>)map.get("messages");
            	for(int j=0;j<messageList.size();j++)
            	{
            		Log.e(TAG, "message_"+j+" is "+messageList.get(j)); 
            		mRevText=messageList.get(j);
            		chatUpdate("other");
            	}
            	// 阅后即焚
            	messageList.clear();
            	map.put("messagesize","0");
            }
        }
        catch(Exception e)
        {
        	Log.e(TAG, e.toString()); 
        }

		mMessageSpinner = (Spinner) findViewById(R.id.spineer_chat);
		ArrayAdapter<String> adapter;
        adapter = new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        for(int i=0;i<normalMeassgelList.size();i++)
        {
        	adapter.add(normalMeassgelList.get(i));
        }

        mMessageSpinner.setAdapter(adapter);
          //添加Spinner事件监听  
        mMessageSpinner.setOnItemSelectedListener(new Spinner.OnItemSelectedListener()  
                 {  
           
                     @Override  
                     public void onItemSelected(AdapterView<?> arg0, View arg1,  
                             int arg2, long arg3) {  
                         // TODO Auto-generated method stub  
                         messageText.setText(normalMeassgelList.get(arg2));
                         //设置显示当前选择的项  
                         //arg0.setVisibility(View.VISIBLE);  
                     }  
           
                     @Override  
                     public void onNothingSelected(AdapterView<?> arg0) {  
                         // TODO Auto-generated method stub  
                           
                     }  
                       
                 });  
        
    }
    private void chatUpdate(String fromWho)
    {
    	int RId=0;
        String name = getName();
        String date = getDate();
        String msgText = getText();
        if(fromWho=="me")
        {
        	RId = R.layout.list_say_me_item;
        	name = "me";
        }
        else
        {
        	RId = R.layout.list_say_he_item;    
        	msgText=getRevText();
        	name=getFromwho();
        }

        ChatMsgEntity newMessage = new ChatMsgEntity(name, date, msgText, RId);
        chatlist.add(newMessage);
        // list.add(d0);
        
        talkView.setAdapter(new ChatMsgViewAdapter(ChatActivity.this, chatlist));
        //messageText.setText("");
        talkView.setSelection(chatlist.size()-1);

        // myAdapter.notifyDataSetChanged();
     	return;
    }

    // shuold be redefine in the future
    private String getName() {
        //return getResources().getString(R.string.myDisplayName);
    	return "other";
    	
    }
    
    // shuold be redefine in the future
    private String getDate() {
        Calendar c = Calendar.getInstance();
        String date = String.valueOf(c.get(Calendar.YEAR)) + "-"
                + String.valueOf(c.get(Calendar.MONTH)) + "-" + c.get(Calendar.DAY_OF_MONTH);
        return date;
    }

    // shuold be redefine in the future
    private String getText() {
        return messageText.getText().toString();
    }
    
    private String getRevText() {
        return mRevText;
    }
    private String getFromwho() {
        return talkToWho;
    }
    

    public void onDestroy() {
        Log.v(TAG, "onDestroy>>>>>>");
        // list = null;
        super.onDestroy();
    }
	private Handler mHandler = new Handler() {  
        public void handleMessage (Message msg) {//此方法在ui线程运行  
        	
            switch(msg.what) {  
            case MyConfig.MSG_CHAT_UPDATE: 
            	String str = (String)msg.obj;
            	Log.e(TAG, "handleMessage>>>>>> str is"+str);
            	String temp[] = str.split(":");
            	String mFromWho=temp[0];
            	mRevText=temp[1];
            	if(!talkToWho.equalsIgnoreCase(mFromWho))
            	{
            		return;
            	}
            	chatUpdate("other");
                break;  
           }  
         }  
     }; 

}
