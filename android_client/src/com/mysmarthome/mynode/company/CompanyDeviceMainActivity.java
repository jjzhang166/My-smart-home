package com.mysmarthome.mynode.company;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;

import com.mysmarthome.mynode.R;
import com.mysmarthome.mynode.R.layout;
import com.mysmarthome.mynode.R.menu;
import com.mysmarthome.mynode.LoginActivity;
import com.mysmarthome.mynode.MyConfig;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.app.Activity;
import android.app.DatePickerDialog;
import android.app.TimePickerDialog;
import android.util.Log;
import android.util.TypedValue;
import android.view.Menu;
import android.view.View;
import android.view.ext.SatelliteMenu;
import android.view.ext.SatelliteMenu.SateliteClickedListener;
import android.view.ext.SatelliteMenuItem;
import android.widget.DatePicker;
import android.widget.Toast;

public class CompanyDeviceMainActivity extends Activity {

	private Thread mThread; 
	public Calendar  c;
	public DatePickerDialog datePicker;
	public TimePickerDialog timePicker;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_company_device_main);
		
		Log.e("device", "find");

        SatelliteMenu menu = (SatelliteMenu) findViewById(R.id.devicemenu);

       
        
		//  Set from XML, possible to programmatically set        
        float distance = TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, 170, getResources().getDisplayMetrics());
        menu.setSatelliteDistance((int) distance);
        menu.setExpandDuration(500);
        menu.setCloseItemsOnClick(true);
        menu.setTotalSpacingDegree(90);
        menu.setMainImage(R.drawable.sat_main);
        //menu.setScaleY((float) 0.8);
        //menu.setScaleX((float) 0.8);
        
        
        Log.e("device", "setMainImage");
        
        List<SatelliteMenuItem> items = new ArrayList<SatelliteMenuItem>();
        //items.add(new SatelliteMenuItem(0, R.drawable.sat_item));
       // items.add(new SatelliteMenuItem(1, R.drawable.sat_item));
       // items.add(new SatelliteMenuItem(2, R.drawable.sat_item));
       // items.add(new SatelliteMenuItem(3, R.drawable.sat_item));
       // items.add(new SatelliteMenuItem(4, R.drawable.sat_item));
       // items.add(new SatelliteMenuItem(5, R.drawable.sat_item));
        items.add(new SatelliteMenuItem(4, R.drawable.ic_3));
        items.add(new SatelliteMenuItem(4, R.drawable.ic_4));
        items.add(new SatelliteMenuItem(3, R.drawable.ic_5));
        items.add(new SatelliteMenuItem(2, R.drawable.ic_6));
        items.add(new SatelliteMenuItem(1, R.drawable.ic_2));
        SatelliteMenuItem xxx = new SatelliteMenuItem(1, R.drawable.ic_2);
        
//        items.add(new SatelliteMenuItem(5, R.drawable.sat_item));
        menu.addItems(items);  
        
        menu.setOnItemClickedListener(new SateliteClickedListener() {
			
			public void eventOccured(int id) {
				Log.e("sat", "Clicked on " + id);
			    //mThread = new Thread(runnable);  
			    //mThread.start();
				pickTime();
			}
		});	
        
        
		 c = Calendar.getInstance();
		 datePicker = new DatePickerDialog(CompanyDeviceMainActivity.this,
				new DatePickerDialog.OnDateSetListener() {
					
					@Override
					public void onDateSet(DatePicker view, int year, int monthOfYear,
							int dayOfMonth) {
						// TODO Auto-generated method stub
						
					}
				}
				             ,c.get(Calendar.YEAR),
				              c.get(Calendar.MONTH),
				              c.get(Calendar.DAY_OF_MONTH));
		 
		// timePicker = 
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.company_device_main, menu);
		return true;
	}
	public void  pickTime()
	{
		datePicker.show();
	}
	
	Runnable runnable = new Runnable() {
		public void run() {
			pickTime();
		}
	};
	
    private Handler mHandler = new Handler() {  
        public void handleMessage (Message msg) {//此方法在ui线程运行  
            switch(msg.what) {  
            case MyConfig.MSG_LOGIN_USERID:  
            	//textview_userid.setText((String)msg.obj);
            	MyConfig.USERID=(String)msg.obj;
                break; 
           }  
           // proressBar.setVisibility(View.INVISIBLE);
         }  
     }; 

}
