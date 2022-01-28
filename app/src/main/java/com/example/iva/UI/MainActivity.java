package com.example.iva.UI;

import android.Manifest;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.WindowManager;
import android.widget.CompoundButton;
import android.widget.ImageButton;
import android.widget.Toast;

import com.example.iva.Audio.IVAProcessor;
import com.example.iva.Audio.PreferredMic;
import com.example.iva.Database.Preferences;
import com.example.iva.Database.PreferencesLab;
import com.example.iva.R;

import androidx.appcompat.widget.SwitchCompat;

public class MainActivity extends PermissionActivity {

    private static final String TAG = MainActivity.class.getName();

    private static final String[] PERMISSIONS = {
            Manifest.permission.RECORD_AUDIO,
            Manifest.permission.WRITE_EXTERNAL_STORAGE
    };

    private SwitchCompat mProcessorSwitch;
    private ImageButton mSignalOneButton;
    private ImageButton mSignalTwoButton;

    private boolean mIsProcessorOn = false;
    private int mActiveSignal = 0; // 0 for no active signal, 1 for signal 1, 2 for signal 2

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // keep screen on all the time
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);

        // setup parameters
        setupProcessorSwitch();
        setupSignalOneButton();
        setupSignalTwoButton();
    }

    private void setupProcessorSwitch() {
        mProcessorSwitch = findViewById(R.id.processor_switch);
        mProcessorSwitch.setSoundEffectsEnabled(false);
        mProcessorSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean isChecked) {
                mIsProcessorOn = isChecked;
                IVAProcessor.setIsProcessorOn(mIsProcessorOn);
            }
        });
    }

    private void setupSignalOneButton() {
        mSignalOneButton = findViewById(R.id.signal_one_button);
        mSignalOneButton.setSoundEffectsEnabled(false);
        mSignalOneButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                switch (mActiveSignal) {
                    case 0:
                        mActiveSignal = 1;
                        mSignalOneButton.setImageResource(R.drawable.pause);
                        break;
                    case 1:
                        mActiveSignal = 0;
                        mSignalOneButton.setImageResource(R.drawable.play);
                        break;
                    case 2:
                        mActiveSignal = 1;
                        mSignalTwoButton.setImageResource(R.drawable.play);
                        mSignalOneButton.setImageResource(R.drawable.pause);
                        break;
                }
                IVAProcessor.setActiveInputChannel(mActiveSignal);
            }
        });
    }

    private void setupSignalTwoButton() {
        mSignalTwoButton = findViewById(R.id.signal_two_button);
        mSignalTwoButton.setSoundEffectsEnabled(false);
        mSignalTwoButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                switch (mActiveSignal) {
                    case 0:
                        mActiveSignal = 2;
                        mSignalTwoButton.setImageResource(R.drawable.pause);
                        break;
                    case 1:
                        mActiveSignal = 2;
                        mSignalOneButton.setImageResource(R.drawable.play);
                        mSignalTwoButton.setImageResource(R.drawable.pause);
                        break;
                    case 2:
                        mActiveSignal = 0;
                        mSignalTwoButton.setImageResource(R.drawable.play);
                        break;
                }
                IVAProcessor.setActiveInputChannel(mActiveSignal);
            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();

        // check for permissions when app resumes
        checkPermissions(PERMISSIONS);
    }

    @Override
    protected void onPause() {
        super.onPause();
        stopAudioEngine();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.preferences, menu);
        return true;
    }

    @Override
    protected void onPermissionsNotGranted(String[] missingPermissions) {
        Toast.makeText(this, R.string.permissions_not_granted, Toast.LENGTH_LONG).show();
    }

    @Override
    protected void onPermissionsGranted() {
        startAudioEngine();
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        switch (item.getItemId()) {
            case R.id.preferences:
                startPreferencesActivity();
                return true;
            default:
                return super.onOptionsItemSelected(item);
        }
    }

    private void startPreferencesActivity() {
        Intent intent = new Intent(MainActivity.this, PreferencesActivity.class);
        startActivity(intent);
    }

    private void startAudioEngine() {
        PreferredMic mic = PreferredMic.get(this);
        Preferences preferences = PreferencesLab.get(this).getPreferences();
        IVAProcessor.create(mic.getId(), preferences.learningRate, preferences.normalizationFactor);
        IVAProcessor.start();
    }

    private void stopAudioEngine() {
        IVAProcessor.stop();
        IVAProcessor.delete();
    }
}