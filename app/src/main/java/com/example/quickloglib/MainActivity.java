package com.example.quickloglib;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.example.quickloglib.databinding.ActivityMainBinding;

import java.util.Timer;
import java.util.TimerTask;

public class MainActivity extends AppCompatActivity {
    Timer timer = new Timer();
    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        String logDir = getExternalCacheDir().getAbsolutePath();
        Log.d("MainAc", "onCreate:" + logDir);
        QuickLog.startQuickLog("QuickLogTest", logDir, 1, "PwxA6KeauvGDuekW");
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                Log.d("MainAc", "appendlog");
                for(int i = 0; i < 1000; i++) {
                    Log.d("MainAc", "appendlog while:" + i);
                    QuickLog.appendLog(3,
                            "android",
                            "MainAc",
                            "onCreate",
                            100, 300,
                            400, 0, "hello word is ok~~~~~ andirod:" + i );
                }

            }
        }, 2000);

    }
}