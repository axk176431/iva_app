//
// Created by axk176431 on 4/6/2021.
//

#include "AudioIOEngine.h"
#include <logging_macros.h>

void AudioIOEngine::init(AudioParams audioParams) {
    mAudioParams = audioParams;
    RingBuffer::setBufferSize((audioParams.frameSize + audioParams.hopSize) *
                              audioParams.inputChannelCount);
    AudioOutputEngine::setSampleRate(audioParams.sampleRate);
    AudioOutputEngine::setFramesPerBurst(audioParams.hopSize);
    AudioInputEngine::setSampleRate(audioParams.sampleRate);
    AudioInputEngine::setInputDevice(audioParams.inputDeviceId, audioParams.inputChannelCount);
}

bool AudioIOEngine::start() {
    bool outputStarted = AudioOutputEngine::start();
    bool inputStarted = AudioInputEngine::start();
    return outputStarted && inputStarted;
    return false;
}

void AudioIOEngine::stop() {
    AudioOutputEngine::stop();
    AudioInputEngine::stop();
}

void AudioIOEngine::onAudioInputReady(float *inputData, int32_t numFrames) {
    mMutex.lock();
    if (mSkipInputFrames > 0) {
        mSkipInputFrames--;
    } else {
        RingBuffer::write(inputData, numFrames * mAudioParams.inputChannelCount);
    }
    mMutex.unlock();
}

void AudioIOEngine::onAudioOutputReady(float *outputData, int32_t numFrames) {

    assert(numFrames == mAudioParams.hopSize);

    // write silence to avoid glitches
    memset(outputData, 0, numFrames * sizeof(float));

    mMutex.lock();
    if (mStartWritingToOutput || RingBuffer::isFull()) {
        mStartWritingToOutput = true;
        int32_t inputChannelCount = mAudioParams.inputChannelCount;
        float inputData[mAudioParams.frameSize * inputChannelCount];
        bool isRead = RingBuffer::overlapRead(inputData,
                mAudioParams.frameSize * inputChannelCount,
                mAudioParams.hopSize * inputChannelCount);
        if (isRead && mChannelId > 0) {
            if (mIsProcessorOn) {
                processFrame(inputData, outputData, mChannelId);
            } else {
                // output unprocessed input for selected channel ID
                for (int i = 0; i < mAudioParams.hopSize; i++) {
                    outputData[i] = inputData[i * inputChannelCount + mChannelId - 1];
                }
            }
        }
    }
    mMutex.unlock();
}

void AudioIOEngine::setActiveInputChannel(int32_t channelId) {
    mMutex.lock();
    mChannelId = channelId;
    mMutex.unlock();
}

void AudioIOEngine::setIsProcessorOn(bool isProcessorOn) {
    mIsProcessorOn = isProcessorOn;
}
