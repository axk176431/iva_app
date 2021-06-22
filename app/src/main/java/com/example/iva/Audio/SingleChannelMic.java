package com.example.iva.Audio;


public class SingleChannelMic {

    public final int deviceId;
    public final int channelId;
    public boolean playing;

    public SingleChannelMic(final int deviceId, final int channelId) {
        this.deviceId = deviceId;
        this.channelId = channelId;
    }
}
