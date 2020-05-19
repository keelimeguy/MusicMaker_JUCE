#include "sine_wave_sound.h"

SineWaveSound::SineWaveSound() {
}

SineWaveSound::~SineWaveSound() {
}

bool SineWaveSound::appliesToNote(int) {
    return true;
}

bool SineWaveSound::appliesToChannel(int) {
    return true;
}
