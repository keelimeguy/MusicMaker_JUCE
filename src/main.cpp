#include "Logger.h"
#include "MidiSynthesizer.h"
#include "Pitch.h"

int main() {
    Logger::Init();

    MidiSynthesizer *player = new MidiSynthesizer();
    auto state = player->getMidiState();

    {
        auto pitch = new Pitch(Note::C, 5);
        state->noteOn(0, pitch->getValue(), 1.0);
    }

    {
        auto pitch = new Pitch(Note::E, 5);
        state->noteOn(0, pitch->getValue(), 1.0);
    }

    {
        auto pitch = new Pitch(Note::G, 5);
        state->noteOn(0, pitch->getValue(), 1.0);
    }

    {
        auto pitch = new Pitch(Note::C, 6);
        state->noteOn(0, pitch->getValue(), 1.0);
    }

    system("pause");

    return 0;
}
