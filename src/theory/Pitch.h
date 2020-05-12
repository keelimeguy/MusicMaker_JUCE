#pragma once

enum Note {
    C = 12, Db, D, Eb, E, F, Gb, G, Ab, A, Bb, B,
};

class Pitch {
public:
    Pitch(Note note, int octave)
        : note(note), octave(octave), value(note + 12 * octave) {
    }

    ~Pitch() {}

    Note getNote() { return note; }
    int getOctave() { return octave; }
    int getValue() { return value; }

private:
    Note note;
    int octave;
    int value;
};
