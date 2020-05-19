#include "sequence.h"

Sequence::Sequence() {
}

Sequence::~Sequence() {
}

const double &Sequence::get_total_beats() const {
    return total_beats_;
}

void Sequence::Add(const PitchBank &notes, double length) {
    beat_sequence_.emplace_back(notes, total_beats_, length);
    total_beats_ += length;
}
