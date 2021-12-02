#include "audio.h"
#include <iostream>

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

void Audio::playSFX(const char *filepath)
{
    engine->play2D(filepath);
}

void Audio::playBGM(const char* filepath)
{
    engine->play2D(filepath, true);
}

void Audio::setVolume(float amount)
{
    engine->setSoundVolume(amount);
}

void Audio::stopAllSound()
{
    engine->stopAllSounds();
}



