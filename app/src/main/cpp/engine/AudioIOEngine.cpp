//
// Created by axk176431 on 4/6/2021.
//

#include "AudioIOEngine.h"
#include "Constants.h"
#include <logging_macros.h>
#include <chrono>

bool AudioIOEngine::start() {
    inputBuffer.setBufferSize(INPUT_BUFFER_SIZE);
    outputBuffer.setBufferSize(OUTPUT_BUFFER_SIZE);
    AudioOutputEngine::setSampleRate(SAMPLE_RATE);
    AudioOutputEngine::setFramesPerBurst(HOP_SIZE);
    AudioInputEngine::setSampleRate(SAMPLE_RATE);
    AudioInputEngine::setFramesPerBurst(HOP_SIZE);
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
    auto t1 = std::chrono::system_clock::now();

    assert(numFrames == HOP_SIZE);

    if (mSkipInputFrames > 0) {
        mSkipInputFrames--;
    } else {
        inputBuffer.write(inputData, INPUT_CHANNEL_COUNT * HOP_SIZE);
        float input[INPUT_CHANNEL_COUNT * FRAME_SIZE];
        bool readSuccessful = inputBuffer.overlapRead(input,
                                           INPUT_CHANNEL_COUNT * FRAME_SIZE,
                                              INPUT_CHANNEL_COUNT * HOP_SIZE);
        if (readSuccessful) {
            float output[HOP_SIZE];
            if (mChannelId > 0) {
                if (mIsProcessorOn) {
                    processFrame(input, output, mChannelId);
                } else {
                    // output unprocessed input for selected channel ID
                    for (int i = 0; i < HOP_SIZE; i++) {
                        output[i] = input[i * INPUT_CHANNEL_COUNT + mChannelId - 1];
                    }
                }
                outputBuffer.write(output, HOP_SIZE);
            }
        }
    }

    auto t2 = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> delay = t2 - t1;
    LOGE("IVA computation delay: %f.", delay.count());
}

void AudioIOEngine::onAudioOutputReady(float *outputData, int32_t numFrames) {
    assert(numFrames == HOP_SIZE);

    // write silence to avoid glitches
    memset(outputData, 0, numFrames * sizeof(float));

    if (mStartWritingToOutput || outputBuffer.isFull()) {
        mStartWritingToOutput = true;
        outputBuffer.read(outputData, numFrames);
    }
}

void AudioIOEngine::setActiveInputChannel(int32_t channelId) {
    mChannelId = channelId;
}

void AudioIOEngine::setIsProcessorOn(bool isProcessorOn) {
    mIsProcessorOn = isProcessorOn;
}
