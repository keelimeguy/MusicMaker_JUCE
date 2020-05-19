#include "synth_audio_source.h"

#include "sine_wave_sound.h"
#include "sine_wave_voice.h"

SynthAudioSource::SynthAudioSource(juce::MidiKeyboardState &keyState, int numVoices)
    : keyboardState_(keyState) {
    for (int i = 0; i < numVoices; ++i)
        synth_.addVoice(new SineWaveVoice());

    synth_.addSound(new SineWaveSound());
}

SynthAudioSource::~SynthAudioSource() {
}

void SynthAudioSource::prepareToPlay(int samplesPerBlockExpected, double sampleRate) {
    synth_.setCurrentPlaybackSampleRate(sampleRate);
}

void SynthAudioSource::releaseResources() {
}

void SynthAudioSource::getNextAudioBlock(const juce::AudioSourceChannelInfo &bufferToFill) {
    bufferToFill.clearActiveBufferRegion();

    juce::MidiBuffer incomingMidi;
    keyboardState_.processNextMidiBuffer(incomingMidi, bufferToFill.startSample, bufferToFill.numSamples, true);

    synth_.renderNextBlock(*bufferToFill.buffer, incomingMidi, bufferToFill.startSample, bufferToFill.numSamples);
}
