#include <jni.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <android/input.h>
#include "AudioEngine.h"
#include "AudioCallback.h"

#include <android/log.h>

#define CB_CLASS "jni/Natives"

/**
 * OnMessage callback
 */
#define CB_CLASS_AUDIO_CB "OnRender"
#define CB_CLASS_AUDIO_SIG "([F)V"


// prototypes

// Lib main Sub
int lib_main(int argc, char **argv);

// Used to get the len of a Java Array
const int getArrayLen(JNIEnv *env, jobjectArray jarray);

// printf str messages back to java
void jni_printf(char *format, ...);

void logInJava(const char *message);

// Global env ref (for callbacks)
static JavaVM *g_VM;


// Global Reference to the native Java class jni.Natives.java
static jclass jNativesCls;

static jmethodID jSendAudioMethod;
static jfloatArray jAudioData;
static int audioSize;

static jmethodID setTextMethod;
static jstring message;


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

    // CLEAN UP
    // Free global array
//    env->DeleteGlobalRef(jAudioData);
//    jAudioData = NULL;

    g_VM->DetachCurrentThread();
}

JNIEXPORT void JNICALL
Java_net_solvetheriddle_wavemaker_MainActivity_setFrequencyA(
        JNIEnv *env,
        jobject /* this */,
        jdouble frequency) {
    audioEngine->setFrequencyA(frequency);
}

JNIEXPORT void JNICALL
Java_net_solvetheriddle_wavemaker_MainActivity_setAmplitudeA(
        JNIEnv *env,
        jobject /* this */,
        jdouble amplitude) {
    audioEngine->setAmplitudeA(amplitude);
}

JNIEXPORT void JNICALL
Java_net_solvetheriddle_wavemaker_MainActivity_setFrequencyB(
        JNIEnv *env,
        jobject /* this */,
        jdouble frequency) {
    audioEngine->setFrequencyB(frequency);
}

JNIEXPORT void JNICALL
Java_net_solvetheriddle_wavemaker_MainActivity_setAmplitudeB(
        JNIEnv *env,
        jobject /* this */,
        jdouble amplitude) {
    audioEngine->setAmplitudeB(amplitude);
}

JNIEXPORT void JNICALL
Java_net_solvetheriddle_wavemaker_MainActivity_initCallback(
        JNIEnv *env,
        jobject thisObj) {


    jint getJavaVMStatus = (*env).GetJavaVM(&g_VM);
    if(getJavaVMStatus == 0){
        logInJava("g_VM should be set");
    } else {
        logInJava("g_VM NOT set");
    }

    jNativesCls = (*env).GetObjectClass(thisObj);

    jSendAudioMethod = (*env).GetStaticMethodID(jNativesCls, CB_CLASS_AUDIO_CB, CB_CLASS_AUDIO_SIG);

    if (jSendAudioMethod == 0) {
        logInJava("Unable to find method OnRender(char[])");
        return;
    }

    jAudioData = (*env).NewFloatArray(1442); // TODO get the size from AudioEngine

    
    
    
    setTextMethod = (*env).GetStaticMethodID(jNativesCls,
                                                           "setText",
                                                           "(Ljava/lang/String;)V");
    if (NULL == setTextMethod) return;
    message = (*env).NewStringUTF("Hello from C");

    // Send Text to Java
    // Get a class reference for this object
//    jclass thisClass = (*env).GetObjectClass(thisObj);
//    jmethodID midCallBackStatic = (*env).GetStaticMethodID(thisClass,
//                                                           "callbackStatic",
//                                                           "(Ljava/lang/String;)V");
//    if (NULL == midCallBackStatic) return;
//    jstring message = (*env).NewStringUTF("Hello from C");
//    const char *resultCStr = (*env).GetStringUTFChars(message, NULL);
//    if (NULL == resultCStr) return;
//    printf("In C, the returned string is %s\n", resultCStr);
//    (*env).CallStaticVoidMethod(thisClass, midCallBackStatic, message);

}


void jni_send_audio(float *audioData, int32_t numFrames) {
//
//    JNIEnv *env;
//    if (!g_VM) {
//        logInJava("No JNI VM available");
//        return;
//    }
//    (*g_VM).AttachCurrentThread(&env, NULL);


//    JNIEnv * g_env;
//    // double check it's all ok
//    int getEnvStat = g_VM->GetEnv((void **)&g_env, JNI_VERSION_1_6);
//    if (getEnvStat == JNI_EDETACHED) {
//        if (g_VM->AttachCurrentThread(&g_env, NULL) != 0) {
//            logInJava("Failed to attach");
//        } else {
//            logInJava("Env attached to Thread");
//        }
//    } else if (getEnvStat == JNI_OK) {
//        logInJava("Env already attached");
//    } else if (getEnvStat == JNI_EVERSION) {
//        logInJava("GetEnv: version not supported");
//    }

//    g_env->CallVoidMethod(g_obj, g_mid, val);



    // Send img back to java.
//    if (jSendAudioMethod) {


//        (*env).SetFloatArrayRegion(jAudioData, 0, numFrames, audioData);
//
//        // Call Java method
//        (*env).CallStaticVoidMethod(jNativesCls
//                , jSendAudioMethod
//                , jAudioData);

//        if (setTextMethod && jNativesCls) {


//        const char *resultCStr = (*g_env).GetStringUTFChars(message, NULL);


//        if (NULL == resultCStr) return;
//            (*g_env).CallStaticVoidMethod(jNativesCls, setTextMethod, message);
//        } else {
//            logInJava("nope");
//        }


//    if (g_env->ExceptionCheck()) {
//        g_env->ExceptionDescribe();
//    }



}

}

void logInJava(const char *message) {
    __android_log_print(ANDROID_LOG_ERROR, "JNI", "%s", message);
}
