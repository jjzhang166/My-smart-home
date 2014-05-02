package net.neilgoodman.android.fragmenttabstutorial.application;


import net.neilgoodman.android.fragmenttabstutorial.model.LocationModel;
import android.app.Application;
import com.example.mynode.*;

import com.example.mynode.*;
public class FragmentTabTutorialApplication extends Application {
    
    // This static field acts as the app's "fake" database of location data.
    public static final LocationModel[] sLocations = { 
       //modified by yongming.li for more feature
    	new LocationModel(0, "登录", R.drawable.main_login),
        new LocationModel(1, "聊天", R.drawable.main_chat),
        new LocationModel(2, "控制", R.drawable.main_node),
        new LocationModel(3, "设置", R.drawable.main_setting),
        new LocationModel(4, "RSS阅读", R.drawable.main_free_message),
        //new LocationModel(5, "其它", R.drawable.main_other)
    };
}