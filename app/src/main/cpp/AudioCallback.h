#ifndef WAVEMAKER_AUDIOCALLBACK_H
#define WAVEMAKER_AUDIOCALLBACK_H

#include <jni.h>

extern "C" void jni_send_audio(float *audioData, int32_t numFrames);


//    AudioCallback();
//class AudioCallback {
//public:

//
//    AudioCallback(JNIEnv &env, jobject &pJobject, jmethodID &pID);
//
//    void printData(float audioData);
//
//private:
//    JNIEnv env;
//    jobject pJobject;
//    jmethodID pID;
//};


#endif //WAVEMAKER_AUDIOCALLBACK_H
