#include "sine_wave_voice.h"

#include "sine_wave_sound.h"

SineWaveVoice::SineWaveVoice() {
}

SineWaveVoice::~SineWaveVoice() {
}

bool SineWaveVoice::canPlaySound(juce::SynthesiserSound *sound) {
    return dynamic_cast<SineWaveSound *>(sound) != nullptr;
}

void SineWaveVoice::startNote(int midiNoteNumber, float velocity,
                              juce::SynthesiserSound *sound,
                              int currentPitchWheelPosition) {
    currentAngle_ = 0.0;
    level_ = velocity * 0.15;
    tailOff_ = 0.0;

    auto cyclesPerSecond = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    auto cyclesPerSample = cyclesPerSecond / getSampleRate();

    angleDelta_ = cyclesPerSample * 2.0 * juce::MathConstants<double>::pi;
}

void SineWaveVoice::renderNextBlock(juce::AudioSampleBuffer &outputBuffer, int startSample, int numSamples) {
    if (angleDelta_ != 0.0) {
        if (tailOff_ > 0.0) {
            while (--numSamples >= 0) {
                auto currentSample = (float)(std::sin(currentAngle_) * level_ * tailOff_);

                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample(i, startSample, currentSample);

                currentAngle_ += angleDelta_;
                ++startSample;

                tailOff_ *= 0.99;

                if (tailOff_ <= 0.005) {
                    clearCurrentNote();

                    angleDelta_ = 0.0;
                    break;
                }
            }
        } else {
            while (--numSamples >= 0) {
                auto currentSample = (float)(std::sin(currentAngle_) * level_);

                for (auto i = outputBuffer.getNumChannels(); --i >= 0;)
                    outputBuffer.addSample(i, startSample, currentSample);

                currentAngle_ += angleDelta_;
                ++startSample;
            }
        }
    }
}

void SineWaveVoice::stopNote(float velocity, bool allowTailOff) {
    if (allowTailOff) {
        if (tailOff_ == 0.0)
            tailOff_ = 1.0;
    } else {
        clearCurrentNote();
        angleDelta_ = 0.0;
    }
}

void SineWaveVoice::pitchWheelMoved(int newPitchWheelValue) {
}

void SineWaveVoice::controllerMoved(int controllerNumber, int newControllerValue) {
}
