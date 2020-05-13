#pragma once

#include "Pitch.h"

class PitchBank {
public:
    PitchBank();
    ~PitchBank();

    void addPitch(Pitch pitch);
    void removePitch(Pitch pitch);
    void order(Pitch bass);

    static PitchBank fromString(std::string chord_str);

    inline std::deque<Pitch>::const_iterator cbegin() const noexcept { return pitches.cbegin(); }
    inline std::deque<Pitch>::const_iterator cend() const noexcept { return pitches.cend(); }

private:
    std::deque<Pitch> pitches;

    static std::regex chord_regex;
    static std::regex noadjust_regex;
    static std::regex addadjust_regex;
    static std::regex susadjust_regex;
    static std::regex addnoadjust_regex;
    static std::regex sharpflatadjust_regex;
};
