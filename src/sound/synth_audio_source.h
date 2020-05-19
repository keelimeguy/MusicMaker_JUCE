#pragma once

#include <JuceHeader.h>

class SynthAudioSource : public juce::AudioSource {
public:
    SynthAudioSource(juce::MidiKeyboardState &keyState, int numVoices);
    ~SynthAudioSource() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;

private:
    juce::MidiKeyboardState &keyboardState_;
    juce::Synthesiser synth_;
};
