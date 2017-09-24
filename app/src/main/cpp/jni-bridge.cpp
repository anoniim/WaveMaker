#include <jni.h>
#include <string>
#include <android/input.h>
#include "AudioEngine.h"

static AudioEngine *audioEngine = new AudioEngine();

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
Java_net_solvetheriddle_wavemaker_MainActivity_callStatic(
        JNIEnv *env,
        jobject thisObj) {

    // Get a class reference for this object
    jclass thisClass = (*env).GetObjectClass(thisObj);

    jmethodID midCallBackStr = (*env).GetMethodID(thisClass,
                                                   "callback", "(Ljava/lang/String;)V");
    if (NULL == midCallBackStr) return;
    printf("In C, call back Java's called(String)\n");
    jstring message = (*env).NewStringUTF("Hello from C");
    (*env).CallVoidMethod(thisObj, midCallBackStr, message);

//    jmethodID midCallBackStatic = (*env).GetStaticMethodID(thisClass,
//                                                            "callbackStatic", "()Ljava/lang/String;");
//    if (NULL == midCallBackStatic) return;
//    jstring resultJNIStr = (*env).CallStaticObjectMethod(thisClass, midCallBackStatic);
//    const char *resultCStr = (*env).GetStringUTFChars(resultJNIStr, NULL);
//    if (NULL == resultCStr) return;
//    printf("In C, the returned string is %s\n", resultCStr);
//    (*env)->ReleaseStringUTFChars(env, resultJNIStr, resultCStr);
}



//JNIEXPORT void JNICALL
//Java_net_solvetheriddle_wavemaker_MainActivity_setOutputListener(
//        JNIEnv *env,
//        jobject obj,
//        jobject outputListener) {
//    jclass listenerClass = (*env).GetObjectClass(outputListener);
//    jmethodID outputMethod = env->GetMethodID(listenerClass, "outputMethod", "(F)V");
//    env->CallVoidMethod(outputListener, outputMethod, output);
//    audioEngine->setOutputListener(outputListener);
//}

}