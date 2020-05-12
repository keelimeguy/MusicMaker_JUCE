#pragma once

#include <JuceHeader.h>

#include "SynthAudioSource.h"

class MidiSynthesizer : public juce::AudioAppComponent {
public:
    MidiSynthesizer(int numVoices);
    ~MidiSynthesizer() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;

protected:
    juce::MidiKeyboardState keyboardState;
    int numVoices;

private:
    SynthAudioSource synthAudioSource;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiSynthesizer)

    void dumpDeviceInfo();
};
