#include <stdint.h>
#include "AudioCallback.h"

class Oscillator {
public:
//    Oscillator();
    void setWaveOn(bool isWaveOn);
    void setSampleRate(int32_t sampleRate);
    void render(float *audioData, int32_t numFrames);
    void setFrequency(double frequency);
    void setAmplitude(double amplitude);

    void setCallback(AudioCallback callback);

private:
    bool isWaveOn_ = false;
    double phase_ = 0.0;
    double sampleRate_ = 0.0;
    double frequency_ = 440.0;
    double amplitude_ = 0.3;
    AudioCallback callback_;
};