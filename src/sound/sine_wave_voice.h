#pragma once

#include <JuceHeader.h>

class SineWaveVoice : public juce::SynthesiserVoice {
public:
    SineWaveVoice();
    ~SineWaveVoice() override;

    bool canPlaySound(juce::SynthesiserSound *sound) override;
    void startNote(int midiNoteNumber, float velocity,
                   juce::SynthesiserSound *sound,
                   int currentPitchWheelPosition) override;
    void renderNextBlock(juce::AudioSampleBuffer &outputBuffer, int startSample, int numSamples) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;

private:
    double currentAngle_ = 0.0;
    double angleDelta_ = 0.0;
    double level_ = 0.0;
    double tailOff_ = 0.0;
};
