#pragma once

#include "pitch.h"
#include "mode.h"
#include "note.h"

class Scale {
public:
    Scale(const Note &root, const Mode &mode, int octave = 4);
    ~Scale();

    Pitch FindPitch(int ordinal) const;

private:
    Pitch root_;
    Mode mode_;
};
