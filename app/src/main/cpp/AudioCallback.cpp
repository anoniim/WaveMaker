#include "AudioCallback.h"

void AudioCallback::printData(float audioData) {
    (env).CallVoidMethod(pJobject, pID, audioData);
}

AudioCallback::AudioCallback(JNIEnv &env1, jobject &pJobject1, jmethodID &pID1) {
    env = env1;
    pJobject = pJobject1;
    pID = pID1;
}

AudioCallback::AudioCallback() {

}
