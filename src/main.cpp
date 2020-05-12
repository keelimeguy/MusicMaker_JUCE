#include "Logger.h"
#include "Synthesizer.h"
#include "Pitch.h"

int main() {
    Logger::Init();

    auto player = std::make_unique<Synthesizer>(4);

    player->addPitch(new Pitch(Note::C, 5));
    std::this_thread::sleep_for(std::chrono::seconds(1));

    player->addPitch(new Pitch(Note::D, 5));
    std::this_thread::sleep_for(std::chrono::seconds(1));

    player->addPitch(new Pitch(Note::E, 5));
    std::this_thread::sleep_for(std::chrono::seconds(1));

    player->addPitch(new Pitch(Note::G, 5));
    std::this_thread::sleep_for(std::chrono::seconds(1));

    player->addPitch(new Pitch(Note::C, 6));

    system("pause");

    return 0;
}
