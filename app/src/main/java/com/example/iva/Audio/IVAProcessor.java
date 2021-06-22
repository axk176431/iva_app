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

//    static final int SAMPLE_RATE = 16000;

//    public static void create(Context context) {
//        PreferredMic mic = PreferredMic.get(context);
//        Preferences preferences = PreferencesLab.get(context).getPreferences();
//        create(mic.getId(), mic.getChannelCount(), SAMPLE_RATE, preferences.frameSize,
//                preferences.hopSize, preferences.learningRate, preferences.normalizationFactor,
//                preferences.pcaSmoothingFactor);
//    }

    // Native methods
    public static native void create(int inputDeviceId,
                                     int inputChannelCount,
                                     int sampleRate,
                                     int frameSize,
                                     int hopSize,
                                     float eta,
                                     float beta,
                                     float lambda);
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
