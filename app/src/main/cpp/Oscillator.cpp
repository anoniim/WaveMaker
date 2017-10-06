#include "Oscillator.h"
#include <math.h>
#include <stdio.h>

#define TWO_PI (3.14159 * 2)

void Oscillator::setSampleRate(int32_t sampleRate) {
    sampleRate_ = (double) sampleRate;
}

void Oscillator::setWaveOn(bool isWaveOn) {
    isWaveOn_ = isWaveOn;
    if (!isWaveOn) phaseA_ = 0;
    if (!isWaveOn) phaseB_ = 0;
}

void Oscillator::render(float *audioData, int32_t numFrames) {

    for (int i = 0; i < numFrames; i++) {

        if (isWaveOn_) {

            // Calculates the next sample value for the sine wave.
            float sampleValueA = (float) (sin(phaseA_) * amplitudeA_);
            float sampleValueB = (float) (sin(phaseB_) * amplitudeB_);
            audioData[i] = sampleValueA + sampleValueB;

            // Increments the phase, handling wrap around.
            phaseA_ += (TWO_PI * frequencyA_) / sampleRate_;
            if (phaseA_ > TWO_PI) phaseA_ -= TWO_PI;

            phaseB_ += (TWO_PI * frequencyB_) / sampleRate_;
            if (phaseB_ > TWO_PI) phaseB_ -= TWO_PI;

        } else {
            // Outputs silence by setting sample value to zero.
            audioData[i] = 0;
        }
    }

//    // TODO pass audioData to Java
////    callback_->run(audioData[0]);
//    jni_send_audio(audioData, numFrames);
}

void Oscillator::setFrequencyA(double frequency){
    frequencyA_ = frequency;
    // TODO pass audioData to Java
//    callback_->run(audioData[0]);
//    jni_send_audio(NULL, NULL);
}

void Oscillator::setAmplitudeA(double amplitude){
    amplitudeA_ = amplitude;
}

void Oscillator::setFrequencyB(jdouble frequency) {
    frequencyB_ = frequency;
}

void Oscillator::setAmplitudeB(jdouble amplitude) {
    amplitudeB_ = amplitude;
}

//void Oscillator::setCallback(AudioCallback callback) {
//    callback_ = callback;
//}

//Oscillator::Oscillator() {
//    callback_ = nullptr;
//}
