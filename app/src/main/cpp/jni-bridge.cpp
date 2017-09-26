#include <jni.h>
#include <string>
#include <android/input.h>
#include "AudioEngine.h"
#include "AudioCallback.h"

static AudioEngine *audioEngine = new AudioEngine();
//static Runnable *runnable = new Runnable();

extern "C" {
JNIEXPORT jstring

JNICALL
Java_net_solvetheriddle_wavemaker_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

JNIEXPORT void JNICALL
Java_net_solvetheriddle_wavemaker_MainActivity_touchEvent(
        JNIEnv *env,
        jobject obj,
        jint action) {
    switch (action) {
        case AMOTION_EVENT_ACTION_DOWN:
            audioEngine->setToneOn(true);
            break;
        case AMOTION_EVENT_ACTION_UP:
            audioEngine->setToneOn(false);
            break;
        default:
            break;
    }
}

JNIEXPORT void JNICALL
Java_net_solvetheriddle_wavemaker_MainActivity_startEngine(
        JNIEnv *env,
        jobject /* this */) {
    audioEngine->start();
}

JNIEXPORT void JNICALL
Java_net_solvetheriddle_wavemaker_MainActivity_stopEngine(
        JNIEnv *env,
        jobject /* this */) {
    audioEngine->stop();
}

JNIEXPORT void JNICALL
Java_net_solvetheriddle_wavemaker_MainActivity_setFrequency(
        JNIEnv *env,
        jobject /* this */,
        jdouble frequency) {
    audioEngine->setFrequency(frequency);
}

JNIEXPORT void JNICALL
Java_net_solvetheriddle_wavemaker_MainActivity_setAmplitude(
        JNIEnv *env,
        jobject /* this */,
        jdouble amplitude) {
    audioEngine->setAmplitude(amplitude);
}

JNIEXPORT void JNICALL
Java_net_solvetheriddle_wavemaker_MainActivity_initCallback(
        JNIEnv *env,
        jobject thisObj) {

    // Get a class reference for this object
    jclass thisClass = (*env).GetObjectClass(thisObj);

    jmethodID midCallBackStr = (*env).GetMethodID(thisClass,
                                                   "setAudioDataText", "(F)V");
    if (NULL == midCallBackStr) return;

    AudioCallback callback(*env, thisObj, midCallBackStr);
    audioEngine->setCallback(callback);
}

}