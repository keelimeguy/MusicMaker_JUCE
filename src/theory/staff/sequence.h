#pragma once

#include "pitch_bank.h"

struct Beat {
    PitchBank notes;
    double start;
    double length;
    double end;

    Beat(const PitchBank &notes, double start, double length)
        : notes(notes), start(start), length(length), end(start + length) {
    }

    const std::string ToString() const {
        return "[" + notes.get_name() + "," + std::to_string(start) + "," + std::to_string(length) + "," + std::to_string(end) + "]";
    }

    bool operator==(const Beat &other) const {
        return notes == other.notes && start == other.start && length == other.length && end == other.end;
    }
    bool operator!=(const Beat &other) const { return !operator==(other); }
};

class Sequence {
public:
    Sequence();
    ~Sequence();

    const double &get_total_beats() const;

    void Add(const PitchBank &notes, double length);

    bool operator==(const Sequence &other) const {
        return beat_sequence_ == other.beat_sequence_ && total_beats_ == other.total_beats_;
    }
    bool operator!=(const Sequence &other) const { return !operator==(other); }

    inline auto cbegin() const noexcept { return beat_sequence_.cbegin(); }
    inline auto cend() const noexcept { return beat_sequence_.cend(); }

private:
    std::vector<Beat> beat_sequence_;
    double total_beats_ = 0.0;
};
