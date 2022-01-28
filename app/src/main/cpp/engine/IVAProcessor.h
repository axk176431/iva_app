//
// Created by axk176431 on 6/16/2021.
//

#ifndef IVA_IVAPROCESSOR_H
#define IVA_IVAPROCESSOR_H

#include "AudioIOEngine.h"
#include "Constants.h"
#include <rtwtypes.h>

class IVAProcessor : public AudioIOEngine {

public:
    IVAProcessor(int32_t inputDeviceId, float eta, float beta);
    virtual void processFrame(float *input, float *output, int32_t source) override;

private:
    float mEta = 0.1;
    float mBeta = 0.75;
    float y[FRAME_SIZE];
    creal32_T G[2 * 2 * K];
    float xi[K];
};

#endif //IVA_IVAPROCESSOR_H
