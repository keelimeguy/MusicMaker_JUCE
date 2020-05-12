#pragma once

#include "MidiSynthesizer.h"
#include "Pitch.h"

class Synthesizer : public MidiSynthesizer {
public:
    Synthesizer(int numVoices);
    ~Synthesizer();

    void addPitch(Pitch &pitch, int channel = 1);
    void removePitch(Pitch &pitch, int channel = 1);
    void stop(int channel = 1);

private:
    int activeVoices = 0;
};
