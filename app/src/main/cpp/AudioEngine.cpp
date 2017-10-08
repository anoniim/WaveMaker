#include  <android/log.h>
#include "AudioEngine.h"

aaudio_data_callback_result_t dataCallback(
        AAudioStream *stream,
        void *userData,
        void *audioData,
        int32_t numFrames) {

    ((Oscillator *) (userData))->render(static_cast<float *>(audioData), numFrames);
    return AAUDIO_CALLBACK_RESULT_CONTINUE;
}

AudioEngine::AudioEngine() {
    oscillator_ = new Oscillator();
}

bool AudioEngine::start() {
    AAudioStreamBuilder *streamBuilder;
    AAudio_createStreamBuilder(&streamBuilder);
    AAudioStreamBuilder_setFormat(streamBuilder, AAUDIO_FORMAT_PCM_FLOAT);
    AAudioStreamBuilder_setChannelCount(streamBuilder, 1);
    AAudioStreamBuilder_setPerformanceMode(streamBuilder, AAUDIO_PERFORMANCE_MODE_LOW_LATENCY);
    AAudioStreamBuilder_setDataCallback(streamBuilder, ::dataCallback, oscillator_);

    // Opens the stream.
    aaudio_result_t result = AAudioStreamBuilder_openStream(streamBuilder, &stream_);
    if (result != AAUDIO_OK) {
        __android_log_print(ANDROID_LOG_ERROR, "AudioEngine", "Error opening stream %s",
                            AAudio_convertResultToText(result));
        return false;
    }

    // Retrieves the sample rate of the stream for our oscillator.
    int32_t sampleRate = AAudioStream_getSampleRate(stream_);
    oscillator_->setSampleRate(sampleRate);

    // Starts the stream.
    result = AAudioStream_requestStart(stream_);
    if (result != AAUDIO_OK) {
        __android_log_print(ANDROID_LOG_ERROR, "AudioEngine", "Error starting stream %s",
                            AAudio_convertResultToText(result));
        return false;
    }

    AAudioStreamBuilder_delete(streamBuilder);
    return true;
}

void AudioEngine::stop() {
    if (stream_ != nullptr) {
        AAudioStream_requestStop(stream_);
        AAudioStream_close(stream_);
    }
}

void AudioEngine::setToneOn(bool isToneOn) {
    oscillator_->setWaveOn(isToneOn);
}

void AudioEngine::setAmpFundamental(double frequency) {
    oscillator_->setAmpTonic(frequency);
}

void AudioEngine::setAmp2x(double amplitude) {
    oscillator_->setAmp2x(amplitude);
}

void AudioEngine::setAmp3x(jdouble frequency) {
    oscillator_->setAmp3x(frequency);
}

void AudioEngine::setAmp4x(jdouble amplitude) {
    oscillator_->setAmp4x(amplitude);
}

void AudioEngine::setAmp5x(jdouble amplitude) {
    oscillator_->setAmp5x(amplitude);
}

void AudioEngine::setAmp6x(jdouble amplitude) {
    oscillator_->setAmp6x(amplitude);
}

void AudioEngine::setAmp7x(jdouble amplitude) {
    oscillator_->setAmp7x(amplitude);
}

void AudioEngine::setAmp8x(jdouble amplitude) {
    oscillator_->setAmp8x(amplitude);
}

//void AudioEngine::setCallback(AudioCallback &callback) {
//    oscillator_->setCallback(callback);
//}

//void AudioEngine::setOutputListener(OutputListener outputListener) {
//    outputListener_ = outputListener;
//}