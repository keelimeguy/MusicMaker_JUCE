#include "synthesizer.h"

Synthesizer::Synthesizer(int num_voices)
    : MidiSynthesizer(num_voices) {
}

Synthesizer::~Synthesizer() {
}

void Synthesizer::AddPitch(const Pitch &pitch, int channel) {
    if (keyboardState_.isNoteOn(channel, pitch.get_value())) {
        PRINT_WARNING("Tried to add pitch that already exists: {}", pitch.get_name());

    } else {
        PRINT_DEBUG("Adding pitch: {}", pitch.get_name());
        keyboardState_.noteOn(channel, pitch.get_value(), 1.0);

        if (++active_voices_ > numVoices_) {
            PRINT_WARNING("More pitches than available voices! ({}>{})", active_voices_, numVoices_);
        }
    }
}

void Synthesizer::RemovePitch(const Pitch &pitch, int channel) {
    if (keyboardState_.isNoteOn(channel, pitch.get_value())) {

        PRINT_DEBUG("Removing pitch: {}", pitch.get_name());
        keyboardState_.noteOff(channel, pitch.get_value(), 1.0);

        --active_voices_;

    } else {
        PRINT_WARNING("Tried to remove pitch that didn't exist: {}", pitch.get_name());
    }
}

void Synthesizer::AddPitchBank(const PitchBank &chord, int channel) {
    for (auto it = chord.cbegin(); it != chord.cend(); ++it) {
        this->AddPitch(*it, channel);
    }
}

void Synthesizer::RemovePitchBank(const PitchBank &chord, int channel) {
    for (auto it = chord.cbegin(); it != chord.cend(); ++it) {
        this->RemovePitch(*it, channel);
    }
}

void Synthesizer::Stop(int channel) {
    keyboardState_.allNotesOff(channel);
}
