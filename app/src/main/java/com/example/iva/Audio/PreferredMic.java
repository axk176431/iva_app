package com.example.iva.Audio;

import android.content.Context;
import android.media.AudioDeviceInfo;
import android.media.AudioManager;
import android.media.MicrophoneInfo;
import android.util.Log;

import java.io.IOException;
import java.util.List;

public class PreferredMic {

    private final int id;
    private final int channelCount;
    private static PreferredMic mPreferredMic;

    private PreferredMic(final int id, final int channelCount) {
        this.id = id;
        this.channelCount = channelCount;
    }

    public static PreferredMic get(final Context context) {
        if (mPreferredMic == null) {
            findBest(context);
        }
        return mPreferredMic;
    }

    private static void findBest(final Context context) {
        AudioManager audioManager = (AudioManager)context.getSystemService(Context.AUDIO_SERVICE);
        assert audioManager != null;
        AudioDeviceInfo[] inputDevices = audioManager.getDevices(AudioManager.GET_DEVICES_INPUTS);
        int deviceId = 0;
        int channelCount = 1;
        for (AudioDeviceInfo curr : inputDevices) {
            if (curr.getType() == AudioDeviceInfo.TYPE_BUILTIN_MIC) {
                Log.d("INPUT", "channel id " + curr.getId() + " channel count " + curr.getChannelCounts().length);
                int n = curr.getChannelCounts().length;
                if (n != 0 && curr.getChannelCounts()[n - 1] >= channelCount) {
                    channelCount = curr.getChannelCounts()[n - 1];
                    deviceId = curr.getId();

                }
            }
        }
        try {
            List<MicrophoneInfo> micList = audioManager.getMicrophones();
            for (MicrophoneInfo mic : micList) {
                Log.d("Mic info", mic.getDescription() + " " + mic.getId() + " " + mic.getGroup() + " " + mic.getIndexInTheGroup() + " " + mic.getDirectionality() + " " + mic.getPosition().x + " " + mic.getPosition().y + " " + mic.getPosition().z);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        mPreferredMic = new PreferredMic(deviceId, channelCount);
    }

    public int getId() {
        return id;
    }

    public int getChannelCount() {
        return channelCount;
    }
}