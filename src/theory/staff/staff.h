#pragma once

#include "staff_iterator.h"
#include "pitch_bank.h"
#include "sequence.h"

class Staff {
public:
    Staff();
    ~Staff();

    void Add(const PitchBank &notes, double length = 1.0, int line = 1);

    StaffIterator begin() { return StaffIterator(lines_, 0.0); }
    StaffIterator end() { return StaffIterator(lines_, total_beats_); }

private:
    std::vector<Sequence> lines_; // Each line is a parallel running sequence of notes
    double total_beats_;
};
