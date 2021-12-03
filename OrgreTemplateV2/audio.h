#pragma once
#ifndef AUDIO_H
#define AUDIO_H

#include <stdio.h>
#include <irrKlang.h>

using namespace irrklang;

#pragma comment(lib, "irrKlang.lib")

/// This class is used to control the game's audio 
class Audio {
protected:
    Audio();
    ~Audio() {};

    static Audio* audio_;
public:
    Audio(Audio& other) = delete;
    void operator=(const Audio&) = delete;
    static Audio* GetInstance();

    void playSFX(const char *filepath);
    void playBGM(const char *filepath);
    void setVolume(float amount);
    void stopAllSound();

private:
    ISoundEngine* engine; 
};

#endif