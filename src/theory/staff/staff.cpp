#include "staff.h"

Staff::Staff() {
}

Staff::~Staff() {
}

void Staff::Add(const PitchBank &notes, double length, int line) {
    assert(line > 0);

    if (line > (int)lines_.size()) {
        lines_.resize(line);
    }

    lines_[line - 1].Add(notes, length);

    if (lines_[line - 1].get_total_beats() > total_beats_) {
        total_beats_ = lines_[line - 1].get_total_beats();
    }
}
