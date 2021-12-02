#pragma once
#ifndef AUDIO_H
#define AUDIO_H

#include <stdio.h>
#include <irrKlang.h>


using namespace irrklang;

#pragma comment(lib, "irrKlang.lib")



class Audio {
protected:
    Audio();
    ~Audio() {};

    static Audio* audio_;
public:
    Audio(Audio& other) = delete;
    void operator=(const Audio&) = delete;
    static Audio* GetInstance();

    void playSound();

private:
    ISoundEngine* engine; 
};

#endif