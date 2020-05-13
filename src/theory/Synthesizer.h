#pragma once

#include "MidiSynthesizer.h"
#include "PitchBank.h"
#include "Pitch.h"

class Synthesizer : public MidiSynthesizer {
public:
    Synthesizer(int numVoices);
    ~Synthesizer();

    void addPitch(const Pitch &pitch, int channel = 1);
    void removePitch(const Pitch &pitch, int channel = 1);

    void addPitchBank(const PitchBank &chord, int channel = 1);
    void removePitchBank(const PitchBank &chord, int channel = 1);

    void stop(int channel = 1);

private:
    int activeVoices = 0;
};
