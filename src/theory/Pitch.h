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

private:
    Note note;
    int octave;
    int value;
};
