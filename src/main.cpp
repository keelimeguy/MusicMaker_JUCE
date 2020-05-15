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

void play_chord(std::string chord_str, int length = 0, std::shared_ptr<Synthesizer> player = nullptr) {
    if (player == nullptr) {
        player = std::make_shared<Synthesizer>(5);
    }

    auto chord = PitchBank::fromString(chord_str);

    player->addPitchBank(chord);
    PRINT_LOG("Playing: {}", chord_str);
    if (length > 0) {
        std::this_thread::sleep_for(std::chrono::seconds(length));
    } else {
        system("pause");
    }
    player->removePitchBank(chord);
}

int main(int argc, char *argv[]) {
    Logger::Init();

    if (argc > 1) {
        auto player = std::make_shared<Synthesizer>(5);
        for (int i = 1; i < argc; ++i) {
            play_chord(argv[i], 2, player);
        }
        system("pause");

    } else {
        play_scale(Note::C, Mode::Major);
    }

    return 0;
}
