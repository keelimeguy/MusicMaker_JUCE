#pragma once

#include "Note.h"

class Pitch {
public:
    Pitch(Note note, int octave = 4);
    ~Pitch();

    Note getNote() const;
    int getOctave() const;
    int getValue() const;
    std::string getName() const;

    void setOctave(int octave);

    Pitch transpose(int steps);
    Pitch flat();
    Pitch sharp();

    friend inline bool operator<(const Pitch &a, const Pitch &b) { return a.value < b.value; }
    friend inline bool operator>(const Pitch &a, const Pitch &b) { return b < a; }
    friend inline bool operator<=(const Pitch &a, const Pitch &b) { return !(a > b); }
    friend inline bool operator>=(const Pitch &a, const Pitch &b) { return !(a < b); }
    friend inline bool operator==(const Pitch &a, const Pitch &b) { return a.value == b.value; }
    friend inline bool operator!=(const Pitch &a, const Pitch &b) { return !(a == b); }

private:
    Note note;
    int octave;
    int value;
};
