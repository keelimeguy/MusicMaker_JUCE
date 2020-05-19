#pragma once

#include "pitch.h"

class PitchBank {
public:
    PitchBank();
    ~PitchBank();

    void AddPitch(const Pitch &pitch);
    void RemovePitch(const Pitch &pitch);
    void Reorder(const Pitch &bass);

    const std::string &get_name() const;

    static const PitchBank FromString(const std::string &chord_str);

    friend inline bool operator==(const PitchBank &a, const PitchBank &b) { return a.pitches_ == b.pitches_; }
    friend inline bool operator!=(const PitchBank &a, const PitchBank &b) { return !(a == b); }

    inline auto cbegin() const noexcept { return pitches_.cbegin(); }
    inline auto cend() const noexcept { return pitches_.cend(); }

private:
    std::deque<Pitch> pitches_;
    std::string name_;

    static std::regex chord_regex_;
    static std::regex noadjust_regex_;
    static std::regex addadjust_regex_;
    static std::regex susadjust_regex_;
    static std::regex addnoadjust_regex_;
    static std::regex sharpflatadjust_regex_;
};
