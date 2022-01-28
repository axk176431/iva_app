#include <jni.h>
#include <string>
#include <logging_macros.h>
#include "engine/IVAProcessor.h"

static IVAProcessor *engine = nullptr;

extern "C" {

JNIEXPORT void JNICALL
Java_com_example_iva_Audio_IVAProcessor_create(JNIEnv *env, jclass clazz,
                          jint input_device_id, jfloat eta, jfloat beta) {
    if (engine != nullptr) {
        LOGE("Error creating audio engine, engine already created.");
    } else {
        engine = new IVAProcessor(input_device_id, eta, beta);
    }
}

JNIEXPORT void JNICALL
Java_com_example_iva_Audio_IVAProcessor_setActiveInputChannel(JNIEnv *env, jclass clazz, jint channelId) {
    if (engine == nullptr) {
        LOGE("Error setting active input channel, engine not created.");
    } else {
        engine->setActiveInputChannel(channelId);
    }
}

JNIEXPORT void JNICALL
Java_com_example_iva_Audio_IVAProcessor_setIsProcessorOn(JNIEnv *env, jclass clazz, jboolean is_processor_on) {
    if (engine == nullptr) {
        LOGE("Error setting up processor, engine not created.");
    } else {
        engine->setIsProcessorOn(is_processor_on);
    }
}

JNIEXPORT void JNICALL
Java_com_example_iva_Audio_IVAProcessor_start(JNIEnv *env, jclass clazz) {
    if (engine == nullptr) {
        LOGE("Error starting audio engine, engine not created.");
    } else {
        if (!engine->start()) {
            LOGE("Error starting audio engine, engine failed to start.");
        }
    }
}

JNIEXPORT void JNICALL
Java_com_example_iva_Audio_IVAProcessor_stop(JNIEnv *env, jclass clazz) {
    if (engine == nullptr) {
        LOGE("Error stopping audio engine, engine not created.");
    } else {
        engine->stop(); // blocking stop
    }
}

JNIEXPORT void JNICALL
Java_com_example_iva_Audio_IVAProcessor_delete(JNIEnv *env, jclass clazz) {
    if (engine == nullptr) {
        LOGE("Error deleting audio engine, engine already deleted.");
    } else {
        delete engine;
        engine = nullptr;
    }
}

} // extern "C"