package com.chipsee.gpiodemo;

import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.CompoundButton;
import android.widget.ImageView;
import android.widget.Switch;
import java.util.ArrayList;
import java.util.Timer;
import java.util.TimerTask;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";

    private Timer timer = new Timer();
    static int j;

    private ImageView imageViewInput;
    private Switch switchOutput1;
    private Switch switchOutput2;
    private Switch switchOutput3;
    private Switch switchOutput4;
    private Switch switchBuzzer;

    ArrayList<GPIO> gpioInList;
    ArrayList<GPIO> gpioOutList;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        timer.schedule(timerTask,100,100);

        /* If your board changed , please modify this */
        init_Normal_GPIO();

        switchOutput1 = (Switch) findViewById(R.id.switchOutput1);
        switchOutput1.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked){
                    if((HardwareControler.setGPIOValue(gpioOutList.get(0).getGPIONum(),GPIOEnum.HIGH)) < 0 )
                        Log.e(TAG, "onCheckedChanged: setGPIOValue 1 error for gpio"+gpioOutList.get(0).getGPIONum());
                }else{
                    if((HardwareControler.setGPIOValue(gpioOutList.get(0).getGPIONum(),GPIOEnum.LOW)) <0 )
                        Log.e(TAG, "onCheckedChanged: setGPIOValue 0 error for gpio"+gpioOutList.get(0).getGPIONum());
                }
            }
        });

        switchOutput2 = (Switch) findViewById(R.id.switchOutput2);
        switchOutput2.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked){
                    if((HardwareControler.setGPIOValue(gpioOutList.get(1).getGPIONum(),GPIOEnum.HIGH)) < 0 )
                        Log.e(TAG, "onCheckedChanged: setGPIOValue 1 error for gpio"+gpioOutList.get(1).getGPIONum());
                }else{
                    if((HardwareControler.setGPIOValue(gpioOutList.get(1).getGPIONum(),GPIOEnum.LOW)) <0 )
                        Log.e(TAG, "onCheckedChanged: setGPIOValue 0 error for gpio"+gpioOutList.get(1).getGPIONum());
                }
            }
        });

        switchOutput3 = (Switch) findViewById(R.id.switchOutput3);
        switchOutput3.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked){
                    if((HardwareControler.setGPIOValue(gpioOutList.get(2).getGPIONum(),GPIOEnum.HIGH)) < 0 )
                        Log.e(TAG, "onCheckedChanged: setGPIOValue 1 error for gpio"+gpioOutList.get(2).getGPIONum());
                }else{
                    if((HardwareControler.setGPIOValue(gpioOutList.get(2).getGPIONum(),GPIOEnum.LOW)) <0 )
                        Log.e(TAG, "onCheckedChanged: setGPIOValue 0 error for gpio"+gpioOutList.get(2).getGPIONum());
                }
            }
        });

        switchOutput4 = (Switch) findViewById(R.id.switchOutput4);
        switchOutput4.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked){
                    if((HardwareControler.setGPIOValue(gpioOutList.get(3).getGPIONum(),GPIOEnum.HIGH)) < 0 )
                        Log.e(TAG, "onCheckedChanged: setGPIOValue 1 error for gpio"+gpioOutList.get(3).getGPIONum());
                }else{
                    if((HardwareControler.setGPIOValue(gpioOutList.get(3).getGPIONum(),GPIOEnum.LOW)) <0 )
                        Log.e(TAG, "onCheckedChanged: setGPIOValue 0 error for gpio"+gpioOutList.get(3).getGPIONum());
                }
            }
        });

        switchBuzzer = (Switch) findViewById(R.id.switchBuzzer);
        switchBuzzer.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if(isChecked){
                    if((HardwareControler.buzzer_open()) < 0 )
                        Log.e(TAG, "onCheckedChanged: buzzer_open error");
                }else{
                    if((HardwareControler.buzzer_close()) <0 )
                        Log.e(TAG, "onCheckedChanged: buzzer_close error");
                }
            }
        });

    }

    private Handler handler = new Handler() {
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case 1:
                    for(int i=0; i<gpioInList.size(); i++){
                        imageViewInput = (ImageView) findViewById(gpioInList.get(i).getGPIOImageID());
                        if(HardwareControler.getGPIOValue(gpioInList.get(i).getGPIONum()) == GPIOEnum.LOW)
                            imageViewInput.setImageResource(R.drawable.io_low);
                        else {
                            if((HardwareControler.getGPIOValue(gpioInList.get(i).getGPIONum())) < 0 )
                                Log.e(TAG, "handleMessage: getGPIOValue Error!!");
                            else
                                imageViewInput.setImageResource(R.drawable.io_high);
                        }
                    }

                    break;
            }
            super.handleMessage(msg);
        }
    };

    private TimerTask timerTask = new TimerTask() {
        @Override
        public void run() {
            Message message = new Message();
            message.what = 1;
            handler.sendMessage(message);
        }
    };

    private void init_Normal_GPIO(){

        // Output GPIO
        gpioOutList = new ArrayList<GPIO>();
        GPIO gpio = new GPIO(GPIOEnum.GPIO1,GPIOEnum.LOW,R.id.switchOutput1);
        gpioOutList.add(gpio);
        gpio = new GPIO(GPIOEnum.GPIO2,GPIOEnum.LOW,R.id.switchOutput2);
        gpioOutList.add(gpio);
        gpio = new GPIO(GPIOEnum.GPIO3,GPIOEnum.LOW,R.id.switchOutput3);
        gpioOutList.add(gpio);
        gpio = new GPIO(GPIOEnum.GPIO4,GPIOEnum.LOW,R.id.switchOutput4);
        gpioOutList.add(gpio);

        // Input GPIO
        gpioInList = new ArrayList<GPIO>();
        gpio = new GPIO(GPIOEnum.GPIO5,R.id.imageViewInput5);
        gpioInList.add(gpio);
        gpio = new GPIO(GPIOEnum.GPIO6,R.id.imageViewInput6);
        gpioInList.add(gpio);
        gpio = new GPIO(GPIOEnum.GPIO7,R.id.imageViewInput7);
        gpioInList.add(gpio);
        gpio = new GPIO(GPIOEnum.GPIO8,R.id.imageViewInput8);
        gpioInList.add(gpio);

        for (int i=0; i<gpioOutList.size(); i++){
            if((HardwareControler.setGPIOValue(gpioOutList.get(i).getGPIONum(),GPIOEnum.LOW)) < 0 )
                Log.e(TAG, "init_Normal_GPIO: setGPIOValue 0 error for gpio"+gpioOutList.get(i).getGPIONum());
        }
    }

    @Override
    public void onDestroy() {
        timer.cancel();
        super.onDestroy();
    }

}
