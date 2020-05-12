#pragma once

#include "Pitch.h"
#include "Mode.h"

class Scale {
public:
    Scale(Note root, Mode mode, int octave = 4)
        : root(root, octave), mode(mode) {
    }

    Pitch getPitch(int ordinal) {
        return root.transpose(mode.findStep(ordinal));
    }

private:
    Pitch root;
    Mode mode;
};
