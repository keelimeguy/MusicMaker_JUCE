#pragma once

#include <JuceHeader.h>

#include "synth_audio_source.h"

class MidiSynthesizer : public juce::AudioAppComponent {
public:
    MidiSynthesizer(int numVoices);
    ~MidiSynthesizer() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;

protected:
    juce::MidiKeyboardState keyboardState_;
    int numVoices_;

private:
    SynthAudioSource synthAudioSource_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiSynthesizer)

    void dumpDeviceInfo();
};
