#include "Oscillator.h"
#include <math.h>
#include <stdio.h>

#define TWO_PI (3.14159 * 2)
#define FREQUENCY_TONIC 220

void Oscillator::setSampleRate(int32_t sampleRate) {
    sampleRate_ = (double) sampleRate;
}

void Oscillator::setWaveOn(bool isWaveOn) {
    isWaveOn_ = isWaveOn;
    {
        phaseTonic = 0;
        phase2ndHarmonic = 0;
        phase3rdHarmonic = 0;
        phase4thHarmonic = 0;
        phase5thHarmonic = 0;
        phase6thHarmonic = 0;
        phase7thHarmonic = 0;
        phase8thHarmonic = 0;
    }
}

void Oscillator::render(float *audioData, int32_t numFrames) {

    for (int i = 0; i < numFrames; i++) {

        if (isWaveOn_) {

            // Calculates the next sample value for the sine wave.
            float sampleValueTonic = (float) (sin(phaseTonic) * amplitudeTonic);
            float sampleValue2ndHarmonic = (float) (sin(phase2ndHarmonic) * amplitude2ndHarmonic);
            float sampleValue3rdHarmonic = (float) (sin(phase3rdHarmonic) * amplitude3rdHarmonic);
            float sampleValue4thHarmonic = (float) (sin(phase4thHarmonic) * amplitude4thHarmonic);
            float sampleValue5thHarmonic = (float) (sin(phase5thHarmonic) * amplitude5thHarmonic);
            float sampleValue6thHarmonic = (float) (sin(phase6thHarmonic) * amplitude6thHarmonic);
            float sampleValue7thHarmonic = (float) (sin(phase7thHarmonic) * amplitude7thHarmonic);
            float sampleValue8thHarmonic = (float) (sin(phase8thHarmonic) * amplitude8thHarmonic);
            audioData[i] = sampleValueTonic
                           + sampleValue2ndHarmonic
                           + sampleValue3rdHarmonic
                           + sampleValue4thHarmonic
                           + sampleValue5thHarmonic
                           + sampleValue6thHarmonic
                           + sampleValue7thHarmonic
                           + sampleValue8thHarmonic;

            // Increments the phase, handling wrap around.
            incrementPhase(phaseTonic, FREQUENCY_TONIC);
            incrementPhase(phase2ndHarmonic, FREQUENCY_TONIC * 2);
            incrementPhase(phase3rdHarmonic, FREQUENCY_TONIC * 3);
            incrementPhase(phase4thHarmonic, FREQUENCY_TONIC * 4);
            incrementPhase(phase5thHarmonic, FREQUENCY_TONIC * 5);
            incrementPhase(phase6thHarmonic, FREQUENCY_TONIC * 6);
            incrementPhase(phase7thHarmonic, FREQUENCY_TONIC * 7);
            incrementPhase(phase8thHarmonic, FREQUENCY_TONIC * 8);


        } else {
            // Outputs silence by setting sample value to zero.
            audioData[i] = 0;
        }
    }

//    // TODO pass audioData to Java
////    callback_->run(audioData[0]);
//    jni_send_audio(audioData, numFrames);
    // TODO pass audioData to Java
//    callback_->run(audioData[0]);
//    jni_send_audio(NULL, NULL);
}

void Oscillator::incrementPhase(double &phase, double frequency) {
    phase += (TWO_PI * frequency) / sampleRate_;
    if (phase > TWO_PI) phase -= TWO_PI;
}

void Oscillator::setAmpTonic(double amplitude) {
    amplitudeTonic = amplitude;
}

void Oscillator::setAmp2x(double amplitude) {
    amplitude2ndHarmonic = amplitude;
}

void Oscillator::setAmp3x(jdouble amplitude) {
    amplitude3rdHarmonic = amplitude;
}

void Oscillator::setAmp4x(jdouble amplitude) {
    amplitude4thHarmonic = amplitude;
}

void Oscillator::setAmp5x(jdouble amplitude) {
    amplitude5thHarmonic = amplitude;
}

void Oscillator::setAmp6x(jdouble amplitude) {
    amplitude6thHarmonic = amplitude;
}

void Oscillator::setAmp7x(jdouble amplitude) {
    amplitude7thHarmonic = amplitude;
}

void Oscillator::setAmp8x(jdouble amplitude) {
    amplitude8thHarmonic = amplitude;
}

//void Oscillator::setCallback(AudioCallback callback) {
//    callback_ = callback;
//}

//Oscillator::Oscillator() {
//    callback_ = nullptr;
//}
