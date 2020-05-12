#include "Synthesizer.h"

Synthesizer::Synthesizer(int numVoices)
    : MidiSynthesizer(numVoices) {
}

Synthesizer::~Synthesizer() {
}

void Synthesizer::addPitch(Pitch &pitch, int channel) {
    PRINT_TRACE("Adding pitch: {}", pitch.getName());
    keyboardState.noteOn(channel, pitch.getValue(), 1.0);

    if (++activeVoices > numVoices) {
        PRINT_WARN("More pitches than available voices! ({}>{})", activeVoices, numVoices);
    }
}

void Synthesizer::removePitch(Pitch &pitch, int channel) {
    PRINT_TRACE("Removing pitch: {}", pitch.getName());
    keyboardState.noteOff(channel, pitch.getValue(), 1.0);

    activeVoices--;
}

void Synthesizer::stop(int channel) {
    keyboardState.allNotesOff(channel);
}
