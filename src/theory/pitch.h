#pragma once

#include "note.h"

class Pitch {
public:
    Pitch(Note note, int octave = 4);
    ~Pitch();

    Note get_note() const;
    int get_octave() const;
    int get_value() const;
    std::string get_name() const;

    void set_octave(int octave);

    Pitch Transpose(int steps);
    Pitch Flat();
    Pitch Sharp();

    friend inline bool operator<(const Pitch &a, const Pitch &b) { return a.value_ < b.value_; }
    friend inline bool operator>(const Pitch &a, const Pitch &b) { return b < a; }
    friend inline bool operator<=(const Pitch &a, const Pitch &b) { return !(a > b); }
    friend inline bool operator>=(const Pitch &a, const Pitch &b) { return !(a < b); }
    friend inline bool operator==(const Pitch &a, const Pitch &b) { return a.value_ == b.value_; }
    friend inline bool operator!=(const Pitch &a, const Pitch &b) { return !(a == b); }

private:
    Note note_;
    int octave_;
    int value_;
};
