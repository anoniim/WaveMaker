#include <stdint.h>
#include "AudioCallback.h"

class Oscillator {
public:
//    Oscillator();
    void setWaveOn(bool isWaveOn);
    void setSampleRate(int32_t sampleRate);
    void render(float *audioData, int32_t numFrames);
    void setAmpTonic(double amplitude);
    void setAmp2x(double amplitude);
    void setAmp3x(jdouble frequency);
    void setAmp4x(jdouble amplitude);
    void setAmp5x(jdouble amplitude);
    void setAmp6x(jdouble amplitude);
    void setAmp7x(jdouble amplitude);
    void setAmp8x(jdouble amplitude);
//    void setCallback(AudioCallback callback);

private:
    bool isWaveOn_ = false;
    double sampleRate_ = 0.0;
    double phaseTonic = 0.0;
    double phase2ndHarmonic = 0.0;
    double phase3rdHarmonic = 0.0;
    double phase4thHarmonic = 0.0;
    double phase5thHarmonic = 0.0;
    double phase6thHarmonic = 0.0;
    double phase7thHarmonic = 0.0;
    double phase8thHarmonic = 0.0;
    double amplitudeTonic = 1;
    double amplitude2ndHarmonic = 0;
    double amplitude3rdHarmonic = 0;
    double amplitude4thHarmonic = 0;
    double amplitude5thHarmonic = 0;
    double amplitude6thHarmonic = 0;
    double amplitude7thHarmonic = 0;
    double amplitude8thHarmonic = 0;
//    AudioCallback callback_;
    void incrementPhase(double &phase, double frequency);
};