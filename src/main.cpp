#include "synthesizer.h"
#include "pitch_bank.h"
#include "scale.h"

namespace musicmaker {
    void PlayScale(Note root, Mode mode) {
        auto player = std::make_unique<Synthesizer>(1);
        auto scale = std::make_unique<Scale>(root, mode);

        int ordinal = 1;
        auto pitch = scale->FindPitch(ordinal);
        auto last_pitch = pitch.Transpose(12);

        while (last_pitch.get_value() != pitch.get_value()) {
            player->AddPitch(pitch);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            player->RemovePitch(pitch);

            pitch = scale->FindPitch(++ordinal);
        }

        player->AddPitch(last_pitch);
        system("pause");
    }

    void PlayChord(std::string chord_str, int length = 0, std::shared_ptr<Synthesizer> player = nullptr) {
        if (player == nullptr) {
            player = std::make_shared<Synthesizer>(5);
        }

        auto chord = PitchBank::FromString(chord_str);

        player->AddPitchBank(chord);
        PRINT_LOG("Playing: {}", chord_str);
        if (length > 0) {
            std::this_thread::sleep_for(std::chrono::seconds(length));
        } else {
            system("pause");
        }
        player->RemovePitchBank(chord);
    }
}

int main(int argc, char *argv[]) {
    Logger::Init();

    if (argc > 1) {
        auto player = std::make_shared<Synthesizer>(5);
        for (int i = 1; i < argc; ++i) {
            musicmaker::PlayChord(argv[i], 2, player);
        }
        system("pause");

    } else {
        musicmaker::PlayScale(Note::C, Mode::Major);
    }

    return 0;
}
