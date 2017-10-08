#include <aaudio/AAudio.h>
#include "Oscillator.h"
#include "AudioCallback.h"

class AudioEngine {
public:
    AudioEngine();

    bool start();
    void stop();
    void setToneOn(bool isToneOn);
    void setAmpFundamental(double frequency);
    void setAmp2x(double amplitude);
    void setAmp3x(jdouble amplitude);
    void setAmp4x(jdouble amplitude);
    void setAmp5x(jdouble amplitude);
    void setAmp6x(jdouble amplitude);
    void setAmp7x(jdouble amplitude);
    void setAmp8x(jdouble amplitude);

//    void setOutputListener(OutputListener outputListener);
//    OutputListener *outputListener_;
//    void setCallback(AudioCallback &callback);

private:
    Oscillator *oscillator_;
    AAudioStream *stream_;
};