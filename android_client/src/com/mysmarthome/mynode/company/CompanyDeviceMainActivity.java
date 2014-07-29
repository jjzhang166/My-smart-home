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
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.util.Log;
import android.util.TypedValue;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.view.ext.SatelliteMenu;
import android.view.ext.SatelliteMenu.SateliteClickedListener;
import android.view.ext.SatelliteMenuItem;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.LinearLayout;
import android.widget.Toast;

public class CompanyDeviceMainActivity extends Activity implements OnClickListener{

	private Thread mThread; 
	public Calendar  c;
	public DatePickerDialog datePicker;
	public TimePickerDialog timePicker;
	
	public Button timerButton;
	public Button lightnessButton;
	public Button colorButton;
	
	public LinearLayout  lightnessLayout;
	public LinearLayout  colorLayout;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_company_device_main);
		          
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
		 
		lightnessButton = (Button) findViewById(R.id.company_device_lightness_button);
		lightnessButton.setOnClickListener(this);
		
	    colorButton = (Button) findViewById(R.id.company_device_color_button);
	    colorButton.setOnClickListener(this);
		
		timerButton = (Button) findViewById(R.id.company_device_timer_button);
		timerButton.setOnClickListener(this);
		
		colorLayout = (LinearLayout) findViewById(R.id.company_device_color_layout);
		lightnessLayout = (LinearLayout) findViewById(R.id.company_device_lightness_layout);

		
		showIndex(0);
	}

    public void showIndex(int index)
    {
		colorLayout.setVisibility(View.GONE);
		lightnessLayout.setVisibility(View.GONE);
		
		if(index==0)
		{
			lightnessLayout.setVisibility(View.VISIBLE);
		}
		if(index==1)
		{
			colorLayout.setVisibility(View.VISIBLE);
		}
		return;
    }
	@Override
	public void onClick(View v) {
				switch (v.getId()) {
				case R.id.company_device_lightness_button:
					showIndex(0);
					break;
				case R.id.company_device_color_button:	
					showIndex(1);
					break;
				case R.id.company_device_timer_button:	
					datePicker.show();
					break;
				default:
					break;
				}
	}	
} 


