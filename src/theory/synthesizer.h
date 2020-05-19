#pragma once

#include "midi_synthesizer.h"
#include "pitch_bank.h"
#include "pitch.h"

class Synthesizer : public MidiSynthesizer {
public:
    Synthesizer(int num_voices);
    ~Synthesizer();

    void AddPitch(const Pitch &pitch, int channel = 1);
    void RemovePitch(const Pitch &pitch, int channel = 1);

    void AddPitchBank(const PitchBank &chord, int channel = 1);
    void RemovePitchBank(const PitchBank &chord, int channel = 1);

    void Stop(int channel = 1);

private:
    int active_voices_ = 0;
};
