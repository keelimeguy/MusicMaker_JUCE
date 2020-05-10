#pragma once

#include <JuceHeader.h>
#include "theory/Pitch.h"

class AudioPlayer : public juce::AudioAppComponent {
public:
    AudioPlayer();
    ~AudioPlayer() override;

    void play_pitch(Pitch *p);
    void prepareToPlay(int samplesPerBlockExpected, double newSampleRate) override;
    void releaseResources() override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) override;

private:
    float phase       = 0.0f;
    float phaseDelta  = 0.0f;
    float amplitude   = 0.2f;

    double sampleRate = 0.0;
    int expectedSamplesPerBlock = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPlayer)

    void dumpDeviceInfo();
};
