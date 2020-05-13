#include "Synthesizer.h"

Synthesizer::Synthesizer(int numVoices)
    : MidiSynthesizer(numVoices) {
}

Synthesizer::~Synthesizer() {
}

void Synthesizer::addPitch(const Pitch &pitch, int channel) {
    if (keyboardState.isNoteOn(channel, pitch.getValue())) {
        PRINT_WARN("Tried to add pitch that already exists: {}", pitch.getName());

    } else {
        PRINT_TRACE("Adding pitch: {}", pitch.getName());
        keyboardState.noteOn(channel, pitch.getValue(), 1.0);

        if (++activeVoices > numVoices) {
            PRINT_WARN("More pitches than available voices! ({}>{})", activeVoices, numVoices);
        }
    }
}

void Synthesizer::removePitch(const Pitch &pitch, int channel) {
    if (keyboardState.isNoteOn(channel, pitch.getValue())) {

        PRINT_TRACE("Removing pitch: {}", pitch.getName());
        keyboardState.noteOff(channel, pitch.getValue(), 1.0);

        activeVoices--;

    } else {
        PRINT_WARN("Tried to remove pitch that didn't exist: {}", pitch.getName());
    }
}

void Synthesizer::addPitchBank(const PitchBank &chord, int channel) {
    for (auto it = chord.cbegin(); it != chord.cend(); ++it) {
        addPitch(*it, channel);
    }
}

void Synthesizer::removePitchBank(const PitchBank &chord, int channel) {
    for (auto it = chord.cbegin(); it != chord.cend(); ++it) {
        removePitch(*it, channel);
    }
}

void Synthesizer::stop(int channel) {
    keyboardState.allNotesOff(channel);
}
