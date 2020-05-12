#pragma once

#include <JuceHeader.h>

class SynthAudioSource : public juce::AudioSource {
public:
    SynthAudioSource(juce::MidiKeyboardState &keyState);
    ~SynthAudioSource() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;

private:
    juce::MidiKeyboardState &keyboardState;
    juce::Synthesiser synth;
};