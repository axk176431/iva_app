//
// Created by axk176431 on 6/16/2021.
//
#include <logging_macros.h>
#include <fft.h>
#include <compute_eig.h>
#include <complex.h>
#include "IVAProcessor.h"
#include "../Eigen/Dense"

IVAProcessor::IVAProcessor(UserPreferences prefs) {
    mPrefs = prefs;
    AudioParams audioParams = prefs.audioParams;
    AudioIOEngine::init(audioParams);

    // initialize real time parameters
    LOGE("Sample rate: %d, frameSize: %d, hopSize: %d, input id: %d, channel count: %d",
            audioParams.sampleRate, audioParams.frameSize, audioParams.hopSize,
            audioParams.inputDeviceId, audioParams.inputChannelCount);

//    for (int i = 0; i < 9; i++) {
//        A[i].re = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
//        A[i].im = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
//        V[i].re = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
//        V[i].im = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
//        D[i].re = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
//        D[i].im = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
//    }
}

IVAProcessor::~IVAProcessor() {

}

void IVAProcessor::processFrame(float *input, float *output, int32_t source) {
    LOGE("Source: %d, hop size: %d, frame size %d, input channel count %d", source, mPrefs.audioParams.hopSize, mPrefs.audioParams.frameSize, mPrefs.audioParams.inputChannelCount);

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

//    compute_iva(input, source, eta, beta, lambda, y, G, xi, mean_X, C_X);
//    Complex x[FRAME_SIZE];
//    for (int i = 0; i < FRAME_SIZE; i++) {
//        x[i] = input[i * NUM_OBS];
//    }
//    CArray X = CArray(x, FRAME_SIZE);
//    fft(X);
//    ifft(X);
    Eigen::MatrixXcf A = Eigen::MatrixXcf::Random(3,3);
    Eigen::ComplexEigenSolver<Eigen::MatrixXcf> ces;
    ces.compute(A);

    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_span = t2 - t1;

    LOGE("IVA computation delay: %f", time_span.count());

    for (int i = 0; i < FRAME_SIZE / 2; i++) {
        output[i] = y[i];
    }
}

void multiply2Matrices(){
    Eigen::MatrixXd M(2,2);
    Eigen::MatrixXd V(2,2);
    for (int i = 0;  i<=1; i++){
        for (int j = 0; j<=1; j++){
            M(i,j) = 1;
            V(i,j) = 2;
        }
    }
    Eigen::MatrixXd Result = M*V;
}

