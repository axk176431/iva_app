//
// Created by axk176431 on 4/8/2021.
//

#ifndef IVA_AUDIOOUTPUTENGINE_H
#define IVA_AUDIOOUTPUTENGINE_H

#include <oboe/Oboe.h>

class AudioOutputEngine : public oboe::AudioStreamCallback {

public:
    virtual bool start();
    virtual void stop();

    virtual void setSampleRate(int32_t sampleRate);
    void setFramesPerBurst(int32_t framesPerBurst);

    //callbacks
    virtual void onAudioOutputReady(float *audioData, int32_t numFrames) = 0;
    oboe::DataCallbackResult onAudioReady(oboe::AudioStream *audioStream,
                                          void *audioData, int32_t numFrames) override;
    void onErrorBeforeClose(oboe::AudioStream *, oboe::Result) override;
    void onErrorAfterClose(oboe::AudioStream *, oboe::Result) override;

private:
    bool mStarted;
    int32_t mOutputDeviceId = oboe::kUnspecified;
    const oboe::AudioFormat mFormat = oboe::AudioFormat::Float;
    oboe::AudioApi mAudioApi = oboe::AudioApi::AAudio;
    int32_t mOutputChannelCount = oboe::ChannelCount::Mono;
    int32_t mSampleRate = oboe::kUnspecified;
    int32_t mFramesPerBurst = oboe::kUnspecified;

    std::shared_ptr<oboe::AudioStream> mOutputStream;
};

#endif //IVA_AUDIOOUTPUTENGINE_H
