#include "Synthesizer.h"
#include "PitchBank.h"
#include "Scale.h"

void play_scale(Note root, Mode mode) {
    auto player = std::make_unique<Synthesizer>(1);
    auto scale = std::make_unique<Scale>(root, mode);

    int ordinal = 1;
    auto pitch = scale->getPitch(ordinal);
    auto last_pitch = pitch.transpose(12);

    while (last_pitch.getValue() != pitch.getValue()) {
        player->addPitch(pitch);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        player->removePitch(pitch);

        pitch = scale->getPitch(++ordinal);
    }

    player->addPitch(last_pitch);
    system("pause");
}

void play_chord(std::string chord_str) {
    auto player = std::make_unique<Synthesizer>(4);
    auto chord = PitchBank::fromString(chord_str);

    player->addPitchBank(chord);
    system("pause");
}

int main() {
    Logger::Init();

    play_scale(Note::C, Mode::Major);
    play_chord("C");
    play_chord("C7");
    play_chord("Cmaj7");

    return 0;
}
