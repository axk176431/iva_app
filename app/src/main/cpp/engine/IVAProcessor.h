//
// Created by axk176431 on 6/16/2021.
//

#ifndef IVA_IVAPROCESSOR_H
#define IVA_IVAPROCESSOR_H

#include "AudioIOEngine.h"
#include <rtwtypes.h>

struct UserPreferences {
    AudioParams audioParams;
    float eta;
    float beta;
    float lambda;
};

static const int NUM_SOURCES = 2;
static const int NUM_OBS = 3;
static const int FRAME_SIZE = 512;
static const int K = FRAME_SIZE / 2 + 1;

class IVAProcessor : public AudioIOEngine {

public:
    IVAProcessor(UserPreferences prefs);
    virtual ~IVAProcessor();
    virtual void processFrame(float *input, float *output, int32_t source) override;

private:
    UserPreferences mPrefs;
    float eta = 0.1;
    float beta = 0.5;
    float lambda = 0.995;
    float y[FRAME_SIZE];
    creal32_T G[NUM_SOURCES * NUM_SOURCES * K];
    float xi[K];
    creal32_T mean_X[NUM_OBS * K];
    creal32_T C_X[NUM_OBS * NUM_OBS * K];
//
//    creal32_T A[9];
//    creal32_T V[9];
//    creal32_T D[9];
};

#endif //IVA_IVAPROCESSOR_H
