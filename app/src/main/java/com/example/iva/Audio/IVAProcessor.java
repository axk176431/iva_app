package com.example.iva.Audio;

import android.content.Context;
import android.media.AudioManager;
import android.os.Build;
import android.util.Log;

import com.example.iva.Database.Preferences;
import com.example.iva.Database.PreferencesLab;

public enum IVAProcessor {

    INSTANCE;

    // Load native library
    static {
        System.loadLibrary("native-lib");
    }

    // Native methods
    public static native void create(int inputDeviceId,
                                     float eta,
                                     float beta);
    public static native void start();
    public static native void stop();
    public static native void delete();
    public static native void setActiveInputChannel(int id);
    public static native void setIsProcessorOn(boolean isBSSOn);

    public static void setDefaultStreamValues(Context context) {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.JELLY_BEAN_MR1) {
            AudioManager myAudioMgr = (AudioManager) context.getSystemService(
                    Context.AUDIO_SERVICE);
            assert myAudioMgr != null;
            String sampleRateStr = myAudioMgr.getProperty(
                    AudioManager.PROPERTY_OUTPUT_SAMPLE_RATE);
            int defaultSampleRate = Integer.parseInt(sampleRateStr);
            String framesPerBurstStr = myAudioMgr.getProperty(
                    AudioManager.PROPERTY_OUTPUT_FRAMES_PER_BUFFER);
            int defaultFramesPerBurst = Integer.parseInt(framesPerBurstStr);
        }
    }
}
