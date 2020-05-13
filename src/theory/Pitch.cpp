#include "Pitch.h"

Pitch::Pitch(Note note, int octave)
    : note(note), octave(octave), value(note + 12 * octave) {
}

Pitch::~Pitch() {}

Note Pitch::getNote() const {
    return note;
}

int Pitch::getOctave() const {
    return octave;
}

int Pitch::getValue() const {
    return value;
}

void Pitch::setOctave(int new_octave) {
    octave = new_octave;
    value = note + 12 * octave;
}

std::string Pitch::getName() const {
    return note.getName() + std::to_string(octave);
}

Pitch Pitch::transpose(int steps) {
    int new_value = (value + steps) % 12 + 12;
    int new_octave = octave + ((value % 12) + steps) / 12;
    return Pitch(Note(static_cast<Note::Value>(new_value)), new_octave);
}

Pitch Pitch::flat() {
    return transpose(-1);
}

Pitch Pitch::sharp() {
    return transpose(1);
}
