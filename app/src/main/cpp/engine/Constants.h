//
// Created by axk176431 on 6/23/2021.
//

#ifndef IVA_CONSTANTS_H
#define IVA_CONSTANTS_H

// Audio IO related
static const int SAMPLE_RATE = 16000;
static const int INPUT_CHANNEL_COUNT = 3;
static const int FRAME_SIZE = 128;
static const int HOP_SIZE = FRAME_SIZE / 2;
static const int INPUT_BUFFER_SIZE = INPUT_CHANNEL_COUNT * (FRAME_SIZE + HOP_SIZE);
static const int OUTPUT_BUFFER_SIZE = HOP_SIZE;

// IVA related
static const int K = FRAME_SIZE / 2 + 1;

#endif //IVA_CONSTANTS_H
