#include "pitch.h"

Pitch::Pitch(Note note, int octave)
    : note_(note), octave_(octave), value_(note + 12 * octave) {
}

Pitch::~Pitch() {}

const Note &Pitch::get_note() const {
    return note_;
}

const int &Pitch::get_octave() const {
    return octave_;
}

const int &Pitch::get_value() const {
    return value_;
}

void Pitch::set_octave(int new_octave) {
    octave_ = new_octave;
    value_ = note_ + 12 * octave_;
}

const std::string Pitch::get_name() const {
    return note_.get_name() + std::to_string(octave_);
}

Pitch Pitch::Transpose(int steps) const {
    int new_value = (value_ + steps) % 12 + 12;
    int new_octave = octave_ + ((value_ % 12) + steps) / 12;
    return Pitch(Note(static_cast<Note::Value>(new_value)), new_octave);
}

Pitch Pitch::Flat() const {
    return this->Transpose(-1);
}

Pitch Pitch::Sharp() const {
    return this->Transpose(1);
}
