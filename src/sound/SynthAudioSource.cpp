#include "SynthAudioSource.h"
#include "SineWaveSound.h"
#include "SineWaveVoice.h"

SynthAudioSource::SynthAudioSource(juce::MidiKeyboardState &keyState, int numVoices)
    : keyboardState(keyState) {
    for (uint8_t i = 0; i < numVoices; ++i)
        synth.addVoice(new SineWaveVoice());

    synth.addSound(new SineWaveSound());
}

SynthAudioSource::~SynthAudioSource() {
}

void SynthAudioSource::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    synth.setCurrentPlaybackSampleRate(sampleRate);
}

void SynthAudioSource::releaseResources() {
}

void SynthAudioSource::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) {
    bufferToFill.clearActiveBufferRegion();

    juce::MidiBuffer incomingMidi;
    keyboardState.processNextMidiBuffer(incomingMidi, bufferToFill.startSample, bufferToFill.numSamples, true);

    synth.renderNextBlock(*bufferToFill.buffer, incomingMidi, bufferToFill.startSample, bufferToFill.numSamples);
}
