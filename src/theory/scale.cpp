#include "scale.h"

Scale::Scale(const Note &root, const Mode &mode, int octave)
    : root_(root, octave), mode_(mode) {
}

Scale::~Scale() {
}

Pitch Scale::FindPitch(int ordinal) const {
    return root_.Transpose(mode_.FindStep(ordinal));
}
