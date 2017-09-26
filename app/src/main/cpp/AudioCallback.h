#ifndef WAVEMAKER_RUNNABLE_H
#define WAVEMAKER_RUNNABLE_H


#include <jni.h>

class AudioCallback {
public:
    AudioCallback();

    AudioCallback(JNIEnv &env, jobject &pJobject, jmethodID &pID);

    void printData(float audioData);

private:
    JNIEnv env;
    jobject pJobject;
    jmethodID pID;
};


#endif //WAVEMAKER_RUNNABLE_H
