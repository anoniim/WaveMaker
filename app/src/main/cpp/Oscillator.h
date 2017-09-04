#include <stdint.h>

class Oscillator {
public:
    void setWaveOn(bool isWaveOn);
    void setSampleRate(int32_t sampleRate);
    void render(float *audioData, int32_t numFrames);
    void setFrequency(double frequency);

private:
    bool isWaveOn_ = false;
    double phase_ = 0.0;
    double sampleRate_ = 0.0;
    double frequency_ = 440.0;
};