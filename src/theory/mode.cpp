#include "mode.h"

Mode::Mode(std::string name, const std::vector<int> &ascending, const std::vector<int> &descending, int octaves)
    : name_(name), ascending_(ascending), descending_(descending), octaves_(octaves) {
    assert(ascending_.size() <= 128);
    assert(descending_.size() <= 128);
    assert(octaves_ <= 11);
}

Mode::Mode(std::string name, const std::vector<int> &ascending)
    : Mode(name, ascending, ascending) {
    std::reverse(descending_.begin(), descending_.end());
}

std::string Mode::get_name() const {
    return name_;
}

int Mode::FindStep(int ordinal) {
    assert(ordinal != 0);
    int step = 0, octave_step = octaves_ * 12;

    std::vector<int> *intervals;
    if (ordinal > 0) {
        intervals = &ascending_;
    } else {
        intervals = &descending_;
        ordinal = -ordinal;
        octave_step = -octave_step;
        step = -12;
    }

    if (ordinal > (int)intervals->size()) {
        step = ((ordinal - 1) / (int)intervals->size()) * octave_step;
        ordinal = (ordinal - 1) % (int)intervals->size();
    } else {
        --ordinal;
    }

    return step + intervals->at(ordinal);
}

Mode Mode::Ionian("Ionian", { 0, 2, 4, 5, 7, 9, 11 });
Mode Mode::Dorian("Dorian", { 0, 2, 3, 5, 7, 9, 10 });
Mode Mode::Phrygian("Phrygian", { 0, 1, 3, 5, 7, 8, 10 });
Mode Mode::Lydian("Lydian", { 0, 2, 4, 6, 7, 9, 11 });
Mode Mode::Mixolydian("Mixolydian", { 0, 2, 4, 5, 7, 9, 10 });
Mode Mode::Aeolian("Aeolian", { 0, 2, 3, 5, 7, 8, 10 });
Mode Mode::Locrian("Locrian", { 0, 1, 3, 5, 6, 8, 10 });

Mode Mode::Major("Major", { 0, 2, 4, 5, 7, 9, 11 });
Mode Mode::Minor("Minor", { 0, 2, 3, 5, 7, 8, 10 });
Mode Mode::NaturalMinor("NaturalMinor", { 0, 2, 3, 5, 7, 8, 10 });
Mode Mode::HarmonicMinor("HarmonicMinor", { 0, 2, 3, 5, 7, 8, 11 });
Mode Mode::MelodicMinor("MelodicMinor", { 0, 2, 3, 5, 7, 9, 11 }, { 10, 8, 7, 5, 3, 2, 0 });

// Foreign scales from www.medianmusic.com/ScaleForeign.html
Mode Mode::Algerian("Algerian", { 0, 2, 3, 5, 6, 7, 8, 11 });
Mode Mode::Arabian("Arabian", { 0, 2, 4, 5, 6, 8, 10 });
Mode Mode::Balinese("Balinese", { 0, 1, 3, 7, 8 });
Mode Mode::Byzantine("Byzantine", { 0, 1, 4, 5, 7, 8, 11 });
Mode Mode::Egyptian("Egyptian", { 0, 2, 5, 7, 10 });
Mode Mode::Ethiopian("Ethiopian", { 0, 2, 3, 5, 7, 8, 10 });
Mode Mode::Hungarian("Hungarian", { 0, 3, 4, 6, 7, 9, 10 });
Mode Mode::Israeli("Israeli", { 0, 1, 4, 5, 7, 8, 10 });
Mode Mode::Japanese("Japanese", { 0, 1, 5, 7, 8 });
Mode Mode::Javanese("Javanese", { 0, 1, 3, 5, 7, 9, 10 });
Mode Mode::Mongolian("Mongolian", { 0, 2, 4, 7, 9 });
Mode Mode::Persian("Persian", { 0, 1, 4, 5, 6, 8, 11 });
Mode Mode::Spanish("Spanish", { 0, 1, 4, 5, 7, 8, 10 });

Mode Mode::InSen("InSen", { 0, 1, 5, 7, 10 });
Mode Mode::Yo("Yo", { 0, 2, 5, 7, 10 }, { 9, 7, 5, 2, 0 });
// Naming of Hirajoshi modes from www.shredaholic.com/user48
Mode Mode::Hirajoshi("Hirajoshi", { 0, 2, 3, 7, 8 });
Mode Mode::Iwato("Iwato", { 0, 1, 5, 6, 10 });
Mode Mode::Kumoi("Kumoi", { 0, 4, 5, 9, 11 });
Mode Mode::HonKumoi("HonKumoi", { 0, 1, 5, 7, 8 });
Mode Mode::Chinese("Chinese", { 0, 4, 6, 7, 11 });

// Bebop scales from www.mattwarnockguitar.com/bebop-scale
Mode Mode::BebopDominant("BebopDominant", { 0, 2, 4, 5, 7, 9, 10, 11 });
Mode Mode::BebopMinor("BebopMinor", { 0, 2, 3, 5, 7, 9, 10, 11 });
Mode Mode::BebopMajor("BebopMajor", { 0, 2, 4, 5, 7, 8, 9, 11 });
Mode Mode::BebopLydianDominant("BebopLydianDominant", { 0, 2, 4, 6, 7, 9, 10, 11 });
Mode Mode::BebopAltered("BebopAltered", { 0, 1, 4, 5, 7, 8, 10, 11 });
Mode Mode::BebopiiV("BebopiiV", { 0, 2, 4, 5, 6, 7, 9, 10, 11 });
Mode Mode::BebopAllanHoldsworth("BebopAllanHoldsworth", { 0, 2, 3, 4, 5, 7, 9, 10, 11 });
// Bebop scales from https://en.wikipedia.org/wiki/Bebop_scale
Mode Mode::BebopDorian("BebopDorian", { 0, 2, 3, 4, 5, 7, 9, 10 });
Mode Mode::BebopMelodicMinor("BebopMelodicMinor", { 0, 2, 3, 5, 7, 8, 9, 11 });
Mode Mode::BebopHarmonicMinor("BebopHarmonicMinor", { 0, 2, 3, 5, 7, 8, 10, 11 });
Mode Mode::BebopNaturalMinor("BebopNaturalMinor", { 0, 2, 3, 5, 7, 8, 10, 11 });

Mode Mode::HarmonicMajor("HarmonicMajor", { 0, 2, 4, 5, 7, 8, 11 });
Mode Mode::DoubleHarmonic("DoubleHarmonic", { 0, 1, 4, 5, 7, 8, 11 });
Mode Mode::Acoustic("Acoustic", { 0, 2, 4, 6, 7, 9, 10 });
Mode Mode::LydianDominant("LydianDominant", { 0, 2, 4, 6, 7, 9, 10 });
Mode Mode::LydianAugmented("LydianAugmented", { 0, 2, 4, 6, 8, 9, 11 });
Mode Mode::MajorBlues("MajorBlues", { 0, 2, 3, 4, 7, 9 });
Mode Mode::MinorBlues("MinorBlues", { 0, 3, 5, 6, 7, 10 });
Mode Mode::Neapolitan("Neapolitan", { 0, 1, 3, 5, 7, 9, 11 });
Mode Mode::NeapolitanMinor("NeapolitanMinor", { 0, 1, 3, 5, 7, 8, 11 });

// Hexatonic from https://en.wikipedia.org/wiki/Hexatonic_scale
Mode Mode::WholeTone("WholeTone", { 0, 2, 4, 6, 8, 10 });
Mode Mode::Augmented("Augmented", { 0, 3, 4, 7, 8, 11 });
Mode Mode::Prometheus("Prometheus", { 0, 2, 4, 6, 9, 10 });
Mode Mode::Blues("Blues", { 0, 3, 5, 6, 7, 10 });
Mode Mode::TriTone("TriTone", { 0, 1, 4, 6, 7, 10 });
Mode Mode::TwoSemitoneTriTone("TwoSemitoneTriTone", { 0, 1, 2, 6, 7, 8 });

Mode Mode::WHDiminished("WHDiminished", { 0, 2, 3, 5, 6, 8, 9, 11 });
Mode Mode::HWDiminished("HWDiminished", { 0, 1, 3, 4, 6, 7, 9, 10 });
Mode Mode::Pentatonic("Pentatonic", { 0, 2, 4, 7, 9 });
Mode Mode::PentatonicMinor("PentatonicMinor", { 0, 2, 3, 7, 8 });
Mode Mode::Chromatic("Chromatic", { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 });

