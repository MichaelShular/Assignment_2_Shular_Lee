#include "audio.h"
#include <iostream>

Audio* Audio::audio_ = nullptr;;

/// The defualt conconstructor 
Audio::Audio()
{
    engine = createIrrKlangDevice();
}

/// Used to get a single instance of the Audio class
/// 
/// @returns the created Audio.
Audio* Audio::GetInstance()
{
    if (audio_ == nullptr) {
        audio_ = new Audio();
    }
    return audio_;
}

/// Used play a single instance of a sound file
/// 
/// @param: a const char of the location of the file
void Audio::playSFX(const char *filepath)
{
    engine->play2D(filepath);
}

/// Used play a loop of a sound file
/// 
/// @param: a const char of the location of the file
void Audio::playBGM(const char* filepath)
{
    engine->play2D(filepath, true);
}

/// Used to set the Volume within the game
/// 
/// @param: a float
void Audio::setVolume(float amount)
{
    engine->setSoundVolume(amount);
}

/// Stop all sounds playing in the game
/// 
void Audio::stopAllSound()
{
    engine->stopAllSounds();
}



