#pragma once

#include "pitch_bank.h"
#include "sequence.h"

class StaffIterator {
public:
    StaffIterator(const std::vector<Sequence> &lines, double current_beat)
        : lines_(lines), current_beat_(current_beat) {
        assert(current_beat >= 0);
        for (auto &line : lines_) {
            auto it = std::find_if(line.cbegin(), line.cend(), [this](const Beat & beat) { return beat.start > current_beat_; });
            beat_iterators_.emplace_back(--it, line.cend());
            notes_.push_back(it->notes);
        }
    }

    ~StaffIterator() {
    }

    typedef std::vector<PitchBank> value_type;
    typedef std::ptrdiff_t difference_type;
    typedef std::vector<PitchBank> *pointer;
    typedef std::vector<PitchBank> &reference;
    typedef std::input_iterator_tag iterator_category;

    const std::vector<PitchBank> &operator*() const { return notes_; }
    const std::vector<PitchBank> *operator->() const { return &(operator*()); }

    bool operator==(const StaffIterator &other) const {
        return lines_ == other.lines_ && current_beat_ == other.current_beat_;
    }
    bool operator!=(const StaffIterator &other) const { return !operator==(other); }

    StaffIterator &operator++() {
        notes_.clear();

        double smallest_endpoint = 0.0;
        for (auto &it : beat_iterators_) {
            if (it.first == it.second) continue;

            auto &beat = it.first;
            if (smallest_endpoint == 0.0 || beat->end < smallest_endpoint) {
                smallest_endpoint = beat->end;
            }
        }

        assert(smallest_endpoint != 0.0);
        current_beat_ = smallest_endpoint;

        for (auto &it : beat_iterators_) {
            if (it.first == it.second) continue;

            auto &beat = it.first;
            if (beat->end <= current_beat_) {
                ++beat;
            }

            if (it.first != it.second) {
                notes_.push_back(beat->notes);
            }
        }

        return *this;
    }

private:
    const std::vector<Sequence> &lines_;
    double current_beat_;

    std::vector<std::pair<std::vector<Beat>::const_iterator, std::vector<Beat>::const_iterator>> beat_iterators_;
    std::vector<PitchBank> notes_;
};
