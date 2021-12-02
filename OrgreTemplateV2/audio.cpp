#include "audio.h"

Audio* Audio::audio_ = nullptr;;

Audio::Audio()
{
    engine = createIrrKlangDevice();
}

Audio* Audio::GetInstance()
{
    if (audio_ == nullptr) {
        audio_ = new Audio();
    }
    return audio_;
}

void Audio::playSound()
{
    engine->play2D("../media/getout.ogg", true);
    engine->setSoundVolume(0.5);
}

//control volume
//add play sound clip with string parameters 

