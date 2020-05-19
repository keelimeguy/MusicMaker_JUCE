#pragma once

class Mode {
public:
    Mode(const std::string &name, const std::vector<int> &ascending, const std::vector<int> &descending, int octaves = 1);
    Mode(const std::string &name, const std::vector<int> &ascending);

    const std::string &get_name() const;

    int FindStep(int ordinal) const;

    static Mode Ionian;
    static Mode Dorian;
    static Mode Phrygian;
    static Mode Lydian;
    static Mode Mixolydian;
    static Mode Aeolian;
    static Mode Locrian;

    static Mode Major;
    static Mode Minor;
    static Mode NaturalMinor;
    static Mode HarmonicMinor;
    static Mode MelodicMinor;

// Foreign scales from www.medianmusic.com/ScaleForeign.html
    static Mode Algerian;
    static Mode Arabian;
    static Mode Balinese;
    static Mode Byzantine;
    static Mode Egyptian;
    static Mode Ethiopian;
    static Mode Hungarian;
    static Mode Israeli;
    static Mode Japanese;
    static Mode Javanese;
    static Mode Mongolian;
    static Mode Persian;
    static Mode Spanish;

    static Mode InSen;
    static Mode Yo;
// Naming of Hirajoshi modes from www.shredaholic.com/user48
    static Mode Hirajoshi;
    static Mode Iwato;
    static Mode Kumoi;
    static Mode HonKumoi;
    static Mode Chinese;

// Bebop scales from www.mattwarnockguitar.com/bebop-scale
    static Mode BebopDominant;
    static Mode BebopMinor;
    static Mode BebopMajor;
    static Mode BebopLydianDominant;
    static Mode BebopAltered;
    static Mode BebopiiV;
    static Mode BebopAllanHoldsworth;
// Bebop scales from https://en.wikipedia.org/wiki/Bebop_scale
    static Mode BebopDorian;
    static Mode BebopMelodicMinor;
    static Mode BebopHarmonicMinor;
    static Mode BebopNaturalMinor;

    static Mode HarmonicMajor;
    static Mode DoubleHarmonic;
    static Mode Acoustic;
    static Mode LydianDominant;
    static Mode LydianAugmented;
    static Mode MajorBlues;
    static Mode MinorBlues;
    static Mode Neapolitan;
    static Mode NeapolitanMinor;

// Hexatonic from https://en.wikipedia.org/wiki/Hexatonic_scale
    static Mode WholeTone;
    static Mode Augmented;
    static Mode Prometheus;
    static Mode Blues;
    static Mode TriTone;
    static Mode TwoSemitoneTriTone;

    static Mode WHDiminished;
    static Mode HWDiminished;
    static Mode Pentatonic;
    static Mode PentatonicMinor;
    static Mode Chromatic;

private:
    std::string name_;
    std::vector<int> ascending_, descending_;
    int octaves_;
};
