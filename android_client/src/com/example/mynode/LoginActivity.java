package com.example.mynode;
  
import android.app.Activity;  
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.os.Bundle;  
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.view.Window;  
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

  
public class LoginActivity extends Activity implements OnClickListener{  
	private  Button login_button;
	private  EditText edittext_name;
	private  EditText edittext_password;
	public  TextView textview_userid;
	
	private String name="";
	private String password="";
	
    private ProgressBar proressBar;


	private Thread mThread; 
    @Override  
    
    public void onCreate(Bundle savedInstanceState) {  
        super.onCreate(savedInstanceState);  
        requestWindowFeature(Window.FEATURE_NO_TITLE);  
        //Log.e("login","onCreate");
        setContentView(R.layout.login); 
        
    	login_button = (Button) findViewById(R.id.signin_button);
    	login_button.setOnClickListener(LoginActivity.this);
    	
    	proressBar = (ProgressBar)findViewById(R.id.progressBar_login);
    	edittext_name=(EditText)findViewById(R.id.username_edit);
    	edittext_password=(EditText)findViewById(R.id.password_edit);
    	
    	textview_userid=(TextView)findViewById(R.id.login_getuserid_textview);
    	
    	
		SharedPreferences  share = LoginActivity.this.getSharedPreferences("perference", MODE_PRIVATE);  
		//Editor editor = share.edit();//取得编辑器  
    	name = share.getString("name", "");//根据key寻找值 参数1 key 参数2 如果没有value显示的内容  
    	password  = share.getString("password", ""); 
    	edittext_name.setText(name);
    	edittext_password.setText(password);
    	proressBar.setIndeterminate(false);
    	proressBar.setVisibility(View.INVISIBLE);  
    	
    }  
    
    public void onClick(View v) {
		//Log.e("main","id is"+R.id.signin_button); 
		
		switch (v.getId()) {
		case R.id.signin_button:
			//Toast.makeText(LoginActivity.this, "login begin",
			//		Toast.LENGTH_SHORT).show();  
			MyConfig.PROTOCOL_CODE=MyConfig.PROTOCOL_CODE_LOGIN;
			name=edittext_name.getText().toString().trim();
			password = edittext_password.getText().toString().trim();
			if(name.length()==0 || password.length()==0)
			{
    			Toast.makeText(LoginActivity.this, "用户名或密码为空",
    					Toast.LENGTH_SHORT).show(); 
				return;
			}
			SharedPreferences  share = LoginActivity.this.getSharedPreferences("perference", MODE_PRIVATE);  
			Editor editor = share.edit();//取得编辑器  
			editor.putString("name", name);//存储配置 参数1 是key 参数2 是值  
			editor.putString("password", password);  
			editor.commit();//提交刷新数据 
			proressBar.setVisibility(View.VISIBLE);  
			proressBar.setIndeterminate(true);
			
    		MyConfig.myClient.setHandle(mHandler);
    		String str = String.format("chat login  %s  %s",
    				     name,password);
    		MyConfig.myClient.insertCmd(str);
    		if(MyConfig.myClient.isRunning==true)
    		{
    			return;
    		}
		    mThread = new Thread(runnable);  
		    mThread.start();
			break;
		default:
			break;
		}
	}
    
    private Handler mHandler = new Handler() {  
        public void handleMessage (Message msg) {//此方法在ui线程运行  
            switch(msg.what) {  
            case MyConfig.MSG_LOGIN_SUCCESS:  
    			Toast.makeText(LoginActivity.this, "登录成功",
    					Toast.LENGTH_SHORT).show(); 
                break;  
            case MyConfig.MSG_LOGIN_FAILURE:  
    			Toast.makeText(LoginActivity.this, "登录失败",
    					Toast.LENGTH_SHORT).show();  
                break; 
            case MyConfig.MSG_LOGIN_USERID:  
            	textview_userid.setText((String)msg.obj);
                break; 
                
           }  
            proressBar.setVisibility(View.INVISIBLE);
         }  
     };  
    Runnable runnable = new Runnable() { 
    	public void run() {
    		//MyClient client = new MyClient();
    		//client.open();

    		MyConfig.myClient.start();
    	}   		
};

}  

