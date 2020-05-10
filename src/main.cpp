#include "Logger.h"

#include "sound/AudioPlayer.h"
#include "theory/Pitch.h"

int main() {
    Logger::Init();

    AudioPlayer *player = new AudioPlayer();
    player->play_pitch(new Pitch(Note::C, 7));

    system("pause");

    return 0;
}
