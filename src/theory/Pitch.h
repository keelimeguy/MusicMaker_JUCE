#pragma once

#include "Note.h"

class Pitch {
public:
    Pitch(Note note, int octave)
        : note(note), octave(octave), value(note + 12 * octave) {
    }

    ~Pitch() {}

    Note getNote() { return note; }
    int getOctave() { return octave; }
    int getValue() { return value; }
    std::string getName() { return note.getName() + std::to_string(octave); }

    Pitch transpose(int steps) {
        int new_value = (value + steps) % 12 + 12;
        int new_octave = octave + ((value % 12) + steps) / 12;
        return Pitch(Note(static_cast<Note::Value>(new_value)), new_octave);
    }

    Pitch flat() {
        return transpose(-1);
    }

    Pitch sharp() {
        return transpose(1);
    }

private:
    Note note;
    int octave;
    int value;
};
