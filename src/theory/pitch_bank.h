#pragma once

#include "pitch.h"

class PitchBank {
public:
    PitchBank();
    ~PitchBank();

    void AddPitch(Pitch pitch);
    void RemovePitch(Pitch pitch);
    void Reorder(Pitch bass);

    static PitchBank FromString(std::string chord_str);

    inline std::deque<Pitch>::const_iterator cbegin() const noexcept { return pitches_.cbegin(); }
    inline std::deque<Pitch>::const_iterator cend() const noexcept { return pitches_.cend(); }

private:
    std::deque<Pitch> pitches_;

    static std::regex chord_regex_;
    static std::regex noadjust_regex_;
    static std::regex addadjust_regex_;
    static std::regex susadjust_regex_;
    static std::regex addnoadjust_regex_;
    static std::regex sharpflatadjust_regex_;
};
