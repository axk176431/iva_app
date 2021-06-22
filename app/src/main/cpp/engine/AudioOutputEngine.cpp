//
// Created by axk176431 on 4/8/2021.
//

#include <logging_macros.h>
#include "AudioOutputEngine.h"

bool AudioOutputEngine::start() {
    if (mStarted) {
        return true;
    }
    mStarted = true;

    // setup output stream parameters
    oboe::AudioStreamBuilder inBuilder;
    (&inBuilder)->setAudioApi(mAudioApi)
            ->setFormat(mFormat)
            ->setSharingMode(oboe::SharingMode::Exclusive)
            ->setPerformanceMode(oboe::PerformanceMode::LowLatency)
            ->setDataCallback(this)
            ->setErrorCallback(this)
            ->setDeviceId(mOutputDeviceId)
            ->setDirection(oboe::Direction::Output)
            ->setChannelCount(mOutputChannelCount)
            ->setSampleRate(mSampleRate)
            ->setFramesPerDataCallback(mFramesPerBurst)
            ->setSampleRateConversionQuality(oboe::SampleRateConversionQuality::Fastest)
            ->setContentType(oboe::Speech);
    oboe::Result result = inBuilder.openStream(mOutputStream);

    // check if stream is setup properly
    if (result != oboe::Result::OK) {
        LOGE("Error setting up output stream parameters.");
        return false;
    }

    // warn if stream is not low latency
    if (mOutputStream->getPerformanceMode() != oboe::PerformanceMode::LowLatency) {
        LOGW("Output stream is NOT low latency. "
             "Check output stream sample format, sample rate and channel count.");
    }

    // start output stream asynchronously
    mOutputStream->requestStart();

    return true;
}

void AudioOutputEngine::stop() {
    if (!mStarted) {
        return;
    }
    mStarted = false;
    oboe::Result result = mOutputStream->stop();
    if (result != oboe::Result::OK) {
        LOGW("Error stopping stream: %s", oboe::convertToText(result));
    }
    result = mOutputStream->close();
    if (result != oboe::Result::OK) {
        LOGE("Error closing stream: %s", oboe::convertToText(result));
    } else {
        LOGW("Successfully closed streams");
    }
    mOutputStream.reset();
}

void AudioOutputEngine::setSampleRate(int32_t sampleRate) {
    mSampleRate = sampleRate;
}

oboe::DataCallbackResult
AudioOutputEngine::onAudioReady(oboe::AudioStream *audioStream,
                                void *audioData, int32_t numFrames) {
    if (!mStarted) {
        return oboe::DataCallbackResult::Stop;
    }
    onAudioOutputReady(static_cast<float *>(audioData), numFrames);
    return oboe::DataCallbackResult::Continue;
}

void AudioOutputEngine::onErrorBeforeClose(oboe::AudioStream * oboeStream, oboe::Result error) {
    LOGE("Output stream Error before close: %s", oboe::convertToText(error));
}

void AudioOutputEngine::onErrorAfterClose(oboe::AudioStream * oboeStream, oboe::Result error) {
    LOGE("Output stream Error before close: %s", oboe::convertToText(error));
}

void AudioOutputEngine::setFramesPerBurst(int32_t framesPerBurst) {
    mFramesPerBurst = framesPerBurst;
}

