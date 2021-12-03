#pragma once
#ifndef _GAME_H_
#define _GAME_H_
#include "Ogre.h"
#include "Application.h"
#include <iostream>
#include "Platform.h"
#include "Doodle.h"
#include "Input.h"
#include "UI.h"
#include "audio.h"


class Game : public Ogre::FrameListener, public InputListener
{
protected:
    Game(Root* root, SceneManager* scn, Camera* cam);
    static Game* application;
public:
    static Game* _game;
    static Game* GetInstance(Root* root, SceneManager* scn, Camera* cam);
private:
    Game(Game& other) = delete;
    void operator=(const Game&) = delete;
    SceneManager* mScnMgr;
    Root* mRoot;
    Camera* mCamera;
    SceneNode* mCamNode;
    Platform* plaform[9];
    Doodle* doodle;
    Input* gameInput;
    UI* gameUI;
    Audio* gameAudio;
    
public:   
    virtual ~Game() { }
    void setup();
    void createScene();
    void createCamera();
    bool keyPressed(const KeyboardEvent& evt);
    //bool mouseMoved(const MouseMotionEvent& e);*/
    void createFrameListener();
    void renderOneFrame();   
    void createTrayListener();
    
    
    Ogre::SceneNode* SinbadNode;
   
};

#endif // _GAME_H_