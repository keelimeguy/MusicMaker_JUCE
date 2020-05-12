#include "Synthesizer.h"
#include "Scale.h"

int main() {
    Logger::Init();

    auto player = std::make_unique<Synthesizer>(1);
    auto scale = std::make_unique<Scale>(Note::C, Mode::Major);

    int ordinal = 1;
    auto pitch = scale->getPitch(ordinal);
    auto last_pitch = pitch.transpose(12);

    while (last_pitch.getValue() != pitch.getValue()) {
        player->addPitch(pitch);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        player->removePitch(pitch);

        pitch = scale->getPitch(++ordinal);
    }

    player->addPitch(last_pitch);
    system("pause");

    return 0;
}
