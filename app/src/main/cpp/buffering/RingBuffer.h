//
// Created by axk176431 on 4/6/2021.
//

#ifndef IVA_RINGBUFFER_H
#define IVA_RINGBUFFER_H

#include <oboe/Oboe.h>

const int32_t CAPACITY = 48000;

class RingBuffer {

public:

    int32_t read(float* readPtr, int32_t numFrames);
    int32_t write(const float* writePtr, int32_t numFrames);
    bool overlapRead(float* readPtr, int32_t numFrames, int32_t overlap);

    int32_t getBufferSize() const;
    int32_t setBufferSize(int32_t bufferSize);
    int32_t getAvailableFrames() const;
    bool isFull() const;

private:
    int32_t mHead = 0;
    int32_t mCount = 0;
    int32_t mBufferSize = CAPACITY;
    float mData[CAPACITY];
};

#endif //IVA_RINGBUFFER_H
