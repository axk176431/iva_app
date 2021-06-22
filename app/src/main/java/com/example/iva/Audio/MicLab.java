package com.example.iva.Audio;

import android.content.Context;

import java.util.ArrayList;
import java.util.List;

public class MicLab {

    private static final String TAG = MicLab.class.getName();

    private static MicLab mMicLab;
    private final List<SingleChannelMic> mMicList = new ArrayList<>();
    private int mActiveChannelId = 0;

    private MicLab(final Context context) {
        initMicsList(context);
    }

    public static MicLab get(final Context context) {
        if (mMicLab == null) {
            mMicLab = new MicLab(context);
        }
        return mMicLab;
    }

    private void initMicsList(final Context context) {
        mMicList.clear();
        PreferredMic preferredMic = PreferredMic.get(context);
        int n = preferredMic.getChannelCount();
        for (int i = 0; i < n; i++) {
            SingleChannelMic mic = new SingleChannelMic(
                    preferredMic.getId(), i + 1);
            mMicList.add(mic);
        }
    }

    public int getNumMics() {
        return mMicList.size();
    }

    public SingleChannelMic getMic(final int channelId) {
        return mMicList.get(channelId);
    }

    public int getActiveChannelId() {
        return mActiveChannelId;
    }

    public void setActiveChannelId(int activeChannelId) {
        mActiveChannelId = activeChannelId;
        int i = 1;
        for (SingleChannelMic mic : mMicList) {
            mic.playing = mActiveChannelId == i;
            i++;
        }
    }
}
