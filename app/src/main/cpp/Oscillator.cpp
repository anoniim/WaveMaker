#include "Oscillator.h"
#include <math.h>

#define TWO_PI (3.14159 * 2)

void Oscillator::setSampleRate(int32_t sampleRate) {
    sampleRate_ = (double) sampleRate;
}

void Oscillator::setWaveOn(bool isWaveOn) {
    isWaveOn_ = isWaveOn;
    if (!isWaveOn) phase_ = 0;
}

void Oscillator::render(float *audioData, int32_t numFrames) {

    for (int i = 0; i < numFrames; i++) {

        if (isWaveOn_) {

            // Calculates the next sample value for the sine wave.
            audioData[i] = (float) (sin(phase_) * amplitude_);

            // Increments the phase, handling wrap around.
            phase_ += (TWO_PI * frequency_) / sampleRate_;
            if (phase_ > TWO_PI) phase_ -= TWO_PI;

        } else {
            // Outputs silence by setting sample value to zero.
            audioData[i] = 0;
        }
    }

    // TODO pass audioData to Java
//    callback_->run(audioData[0]);
    callback_.printData(0);
}

void Oscillator::setFrequency(double frequency){
    frequency_ = frequency;
}

void Oscillator::setAmplitude(double amplitude){
    amplitude_ = amplitude;
}

void Oscillator::setCallback(AudioCallback callback) {
    callback_ = callback;
}

//Oscillator::Oscillator() {
//    callback_ = nullptr;
//}
