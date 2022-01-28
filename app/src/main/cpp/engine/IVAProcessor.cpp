//
// Created by axk176431 on 6/16/2021.
//
#include <logging_macros.h>
#include <fft.h>
#include <init_iva.h>
#include <compute_iva.h>
#include "IVAProcessor.h"

IVAProcessor::IVAProcessor(int32_t inputDeviceId, float eta, float beta) {
    AudioInputEngine::setInputDevice(inputDeviceId, INPUT_CHANNEL_COUNT);
    // initialize IVA parameters
    mEta = eta;
    mBeta = beta;
    init_iva(y, G, xi);
}

void IVAProcessor::processFrame(float *input, float *output, int32_t source) {
    float x[2 * FRAME_SIZE];
    for (int i = 0; i < FRAME_SIZE; i++) {
        x[i * 2] = input[i * INPUT_CHANNEL_COUNT];
        x[i * 2 + 1] = input[i * INPUT_CHANNEL_COUNT + INPUT_CHANNEL_COUNT - 1];
    }
    compute_iva(x, source, mEta, mBeta, y, G, xi);
    for (int i = 0; i < HOP_SIZE; i++) {
        output[i] = y[i];
    }
}

