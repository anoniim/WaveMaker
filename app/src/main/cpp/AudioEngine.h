#include <aaudio/AAudio.h>
#include "Oscillator.h"
#include "AudioCallback.h"

class AudioEngine {
public:
    AudioEngine();

    bool start();
    void stop();
    void setToneOn(bool isToneOn);
    void setFrequency(double frequency);
    void setAmplitude(double amplitude);
//    void setOutputListener(OutputListener outputListener);
//    OutputListener *outputListener_;

    void setCallback(AudioCallback &callback);

private:
    Oscillator *oscillator_;
    AAudioStream *stream_;
};