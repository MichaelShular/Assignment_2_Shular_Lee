#include "Ogre.h"
#include "Application.h"
#include <iostream>
#include "Platform.h"
#include "Doodle.h"

class Game : public Ogre::FrameListener
{

protected:
    Game(Root* root, SceneManager* scn);
    static Game* application;
public:
    static Game* _game;
    static Game* GetInstance(Root* root, SceneManager* scn);
private:
    Game(Game& other) = delete;
    void operator=(const Game&) = delete;
    SceneManager* mScnMgr;
    Root* mRoot;
    Camera* mCamera;
    SceneNode* mCamNode;
    Platform* plaform[9];
    Doodle* doodle;
public:   
    virtual ~Game() {}
    void setup();
    void createScene();
    void createCamera();
    /*bool keyPressed(const KeyboardEvent& evt);
    bool mouseMoved(const MouseMotionEvent& e);*/
    void createFrameListener();
    void renderOneFrame();
    bool keepRunning();
    void Update();
    
    Ogre::SceneNode* SinbadNode;
   
};