//
// Created by axk176431 on 4/5/2021.
//

#ifndef IVA_AUDIOIOENGINE_H
#define IVA_AUDIOIOENGINE_H

#include "AudioInputEngine.h"
#include "AudioOutputEngine.h"
#include "/../buffering/RingBuffer.h"
#include <mutex>
#include <AsyncRingBuffer.h>

class AudioIOEngine : public AudioOutputEngine, public AudioInputEngine {

public:
    virtual void processFrame(float *input, float *output, int32_t source) = 0;
    virtual void onAudioInputReady(float *inputData, int32_t numFrames) override;
    virtual void onAudioOutputReady(float *outputData, int32_t numFrames) override;
    virtual bool start() override;
    virtual void stop() override;
    void setActiveInputChannel(int32_t channelId);
    void setIsProcessorOn(bool isProcessorOn);

private:
    RingBuffer inputBuffer;
    AsyncRingBuffer outputBuffer;
    int32_t mChannelId = 0; // unspecified
    int32_t mSkipInputFrames = 100;
    bool mStartWritingToOutput = false;
    bool mIsProcessorOn = false;
};

#endif //IVA_AUDIOIOENGINE_H
