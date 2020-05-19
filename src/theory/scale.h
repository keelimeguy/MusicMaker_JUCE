#pragma once

#include "pitch.h"
#include "mode.h"
#include "note.h"

class Scale {
public:
    Scale(Note root, Mode mode, int octave = 4);
    ~Scale();

    Pitch FindPitch(int ordinal);

private:
    Pitch root_;
    Mode mode_;
};
