#pragma once

#include <JuceHeader.h>

#include "SynthAudioSource.h"

class MidiSynthesizer : public juce::AudioAppComponent {
public:
    MidiSynthesizer();
    ~MidiSynthesizer() override;

    juce::MidiKeyboardState *getMidiState();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;

private:
    SynthAudioSource synthAudioSource;
    juce::MidiKeyboardState keyboardState;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiSynthesizer)

    void dumpDeviceInfo();
};
