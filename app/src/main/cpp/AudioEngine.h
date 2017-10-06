#include <aaudio/AAudio.h>
#include "Oscillator.h"
#include "AudioCallback.h"

class AudioEngine {
public:
    AudioEngine();

    bool start();
    void stop();
    void setToneOn(bool isToneOn);
    void setFrequencyA(double frequency);
    void setAmplitudeA(double amplitude);
//    void setOutputListener(OutputListener outputListener);
//    OutputListener *outputListener_;

//    void setCallback(AudioCallback &callback);

    void setFrequencyB(jdouble d);

    void setAmplitudeB(jdouble d);

private:
    Oscillator *oscillator_;
    AAudioStream *stream_;
};