#include "SineWaveSound.h"

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
