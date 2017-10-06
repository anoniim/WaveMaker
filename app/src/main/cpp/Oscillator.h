#include <stdint.h>
#include "AudioCallback.h"

class Oscillator {
public:
//    Oscillator();
    void setWaveOn(bool isWaveOn);
    void setSampleRate(int32_t sampleRate);
    void render(float *audioData, int32_t numFrames);
    void setFrequencyA(double frequency);
    void setAmplitudeA(double amplitude);

//    void setCallback(AudioCallback callback);

    void setFrequencyB(jdouble frequency);

    void setAmplitudeB(jdouble amplitude);

private:
    bool isWaveOn_ = false;
    double sampleRate_ = 0.0;
    double phaseA_ = 0.0;
    double frequencyA_ = 440.0;
    double amplitudeA_ = 0.3;
    double phaseB_ = 0.0;
    double frequencyB_ = 440.0;
    double amplitudeB_ = 0.3;
//    AudioCallback callback_;
};