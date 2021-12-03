#include "Game.h"

using namespace Ogre;
using namespace OgreBites;
using namespace std;

Ogre::Vector3 translate(0, 0, 0);
float rotX = 0.0f;
float rotY = 0.0f;
float _movementspeed;
Game* Game::_game = nullptr;

class ExampleFrameListener : public Ogre::FrameListener, public InputListener
{
private:
    Ogre::SceneNode* _sceneNode;
    Ogre::SceneNode* _camNode;
    float _movementspeed;
    float _mousespeed;
public:

    ExampleFrameListener(Ogre::SceneNode* sceneNode, Ogre::SceneNode* camNode)
    {
        _sceneNode = sceneNode;
        _camNode = camNode;
        _movementspeed = 200.0f;
        _mousespeed = 0.02f;
    }

    bool frameStarted(const Ogre::FrameEvent& evt)
    {
        _sceneNode->translate(translate * evt.timeSinceLastFrame);
        translate = Ogre::Vector3(0, 0, 0);
        return true;
    }

    bool frameEnded(const Ogre::FrameEvent& evt)
    {

        //std::cout << "Frame ended" << std::endl;
        return true;
    }

    bool frameRenderingQueued(const Ogre::FrameEvent& evt)
    {
        //std::cout << "Frame queued" << std::endl;
        return true;
    }
};

/// The defualt conconstructor
/// 
/// @param: a Oger::SceneManager
/// @param: a Oger::SceneNode
/// @param: a Oger::Camera
Game::Game(Root* root, SceneManager* scn, Camera* cam)
{
    mRoot = root;
    mScnMgr = scn;
    mCamera = cam;
}

/// Used to get a single instance of the Game class
/// 
/// @param: a Oger::SceneManager
/// @param: a Oger::SceneNode
/// @param: a Oger::Camera
/// @returns the created Game.
Game* Game::GetInstance(Root* root, SceneManager* scn, Camera* cam)
{
    if (_game == nullptr) {
        _game = new Game(root, scn, cam);
    }
    return _game;
}

/// Used to set the class's variables and create any other class instance need for the game
void Game::setup()
{       
    gameUI = UI::GetInstance(Application::GetInstance()->getRenderWindow(), mScnMgr, Application::GetInstance()->getOverlaySystem());
    gameAudio = Audio::GetInstance();
    gamePhysics = Physics::GetInstance();

    // Add Input Listener to Root
    Application::GetInstance()->addInputListener(this);
    createCamera();
    createScene();
    createFrameListener();
    createTrayListener();

    gameInput = Input::GetInstance(mRoot);
}

/// Used to create objects that will be used 
void Game::createScene()
{
    //used to genarate a random seed
    srand(time(NULL));

    //! [turnlights]
    mScnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    //! [turnlights]

    //! [newlight]
    //
    Light* light1 = mScnMgr->createLight("Light1");
    light1->setType(Ogre::Light::LT_DIRECTIONAL);
    // Set Light Color
    light1->setDiffuseColour(1.0f, 1.0f, 1.0f);
    // Set Light Reflective Color
    light1->setSpecularColour(1.0f, 0.0f, 0.0f);
    // Set Light (Range, Brightness, Fade Speed, Rapid Fade Speed)
    light1->setAttenuation(10, 0.5, 0.045, 0.0);

    //Creating light
    Entity* lightEnt = mScnMgr->createEntity("LightEntity", "sphere.mesh");
    SceneNode* lightNode = mScnMgr->createSceneNode("LightNode");
    lightNode->attachObject(light1);
    lightNode->setScale(0.01f, 0.01f, 0.01f);

    mScnMgr->getRootSceneNode()->addChild(lightNode);
    //! [newlight]

    //! [lightpos]
    lightNode->setPosition(0, 4, 10);
    //! [lightpos]

    SinbadNode = mScnMgr->getRootSceneNode()->createChildSceneNode("Node1");

    //Spawning Platforms
    for (int i = 0; i < numberOfPlatforms; i++)
    {
        if (i == 0) {
            plaform[i] = new Platform(mScnMgr, SinbadNode, Ogre::Vector3(0.0f, -10.0f, 0.0f), std::to_string(i));
        }
        else
        {
            plaform[i] = new Platform(mScnMgr, SinbadNode, plaform[i - 1]->GetPosition(), std::to_string(i));
            
        }
    }
    lastPlaformHeight = plaform[numberOfPlatforms - 1]->GetPosition().y;
    
    //Spawning doodle
    doodle = new Doodle(mScnMgr, SinbadNode, plaform[0]->GetPosition());
    
    //Spawning Goal
    goalToReach = new Goal(mScnMgr, SinbadNode, Vector3(0.0f, 40.0f, 0.0f));
    
    //Set game's gravity
    gamePhysics->setGravity(Vector3(0.0f, -0.1f, 0.0f));
   
    //Play BMG music
    gameAudio->playBGM("../media/ophelia.mp3");
    
    //Set volume
    gameAudio->setVolume(0.2f);
}

/// Used to create camera used in game
void Game::createCamera()
{
    //! [camera]
    mCamNode = mScnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    mCamera = mScnMgr->createCamera("myCam");

    mCamera->setNearClipDistance(10); // specific to this sample
    mCamera->setAutoAspectRatio(true);
    mCamNode->attachObject(mCamera);
    mCamNode->setPosition(0, 0, 25);
    mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);

    // and tell it to render into the main window
    Ogre::Viewport* viewport = Application::GetInstance()->getRenderWindow()->addViewport(mCamera);
    viewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));
    mCamera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));

    mCurrentCameraPostion = mCameraPostionToReach = 0;
}

/// Used to listen for what key is pressed 
/// 
/// @returns an bool
bool Game::keyPressed(const KeyboardEvent& evt)
{
    gameInput->Update(evt);
    return true;
}

/// Create FrameLisener and add to root
void Game::createFrameListener()
{
    Ogre::FrameListener* FrameListener = new ExampleFrameListener(SinbadNode, mCamNode);
    mRoot->addFrameListener(FrameListener);
}

/// All game logic the need to happen in each frame
void Game::renderOneFrame()
{ 
    mRoot->renderOneFrame();
    //check if doodle reached the goal
    if (gamePhysics->checkAAABB(doodle->GetWorldAABB(), goalToReach->GetWorldAABB())) {
        doodle->showReset = true;
    }
    //Pause game if true and show reset button
    if (doodle->showReset == true) {
        gameUI->setCaptionForLabel(0, Ogre::StringConverter::toString(mPausedTime));
        gameUI->setTrayVisibility(1, true);
        //Reset button logic if pressed
        if (gameUI->getIsButtonPressed(0) == true) {
            gameUI->setTrayVisibility(1, false);
            //Reseting game objects to play again 
            mCamNode->setPosition(0, 0, 25);
            mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);
            for (int i = 0; i < numberOfPlatforms; i++)
            {
                if (i == 0) {
                    plaform[i]->resetPlaformPosition(Ogre::Vector3(0.0f, -10.0f, 0.0f));
                }
                else
                {
                    plaform[i]->resetPlaformPosition(plaform[i - 1]->GetPosition());

                }
            }
            doodle->resetPosition(plaform[0]->GetPosition());
            timer.reset();
            mCurrentCameraPostion = mCameraPostionToReach = 0;
            lastPlaformHeight = plaform[numberOfPlatforms - 1]->GetPosition().y;
            return;
        }
    }
    else {
        //doodle movement
        if (gameInput->checkIfKeyBeingPressed('a'))
            translate = Ogre::Vector3(-10, 0, 0);
        if (gameInput->checkIfKeyBeingPressed('d'))
            translate = Ogre::Vector3(10, 0, 0);
        //Update Time UI
        gameUI->setCaptionForLabel(0, Ogre::StringConverter::toString(timer.getMilliseconds() / 1000));
        mPausedTime = timer.getMilliseconds() / 1000; 
        //Update doodle
        doodle->Update(gamePhysics->getGravity(), mCamNode->getPosition().y);
        //Used to see if camera needs to move
        mCameraPostionToReach = doodle->getApexHeight();
    }
    //Check if application need to close
    if (gameInput->checkIfKeyBeingPressed(SDLK_ESCAPE)) {
        mRoot->queueEndRendering();
        Application::GetInstance()->setIsRunning(false);
    }
    //Game Collision
    if (doodle->getIsFalling()) {
        for (int i = 0; i < numberOfPlatforms; i++)
        {
            //Check is platform is below a certain distance then move to new position
            if (plaform[i]->GetPosition().y < mCamNode->getPosition().y && std::abs(plaform[i]->GetPosition().y - mCamNode->getPosition().y) > 11) {
                plaform[i]->setNewPostion(lastPlaformHeight);
                lastPlaformHeight = plaform[i]->GetPosition().y;
            }
            //Check if doodle collides with platform
            if (gamePhysics->checkAAABB(doodle->GetWorldAABB(), plaform[i]->GetWorldAABB())) {
                doodle->setIsFalling(false);
                gameAudio->playSFX("../media/jump.wav");
            }
        }
    }
    //Camera Movement in game
    if (mCurrentCameraPostion < mCameraPostionToReach) {
        mCamNode->lookAt(Vector3(0, mCamNode->getPosition().y + 0.05f, 0), Node::TS_WORLD);
        mCamNode->setPosition(0, mCamNode->getPosition().y + 0.1f, 25);
        mCurrentCameraPostion = mCamNode->getPosition().y;
    }
    //Reset Input of what key is pressed
    gameInput->reset();
}


///Create all trays in the scene with what UI objects are in them.
void Game::createTrayListener()
{
    //Creating stats UI
    Application::GetInstance()->addInputListener(gameUI->addedTrayMgr("InterfaceName", true));
    gameUI->addedFrameStatsToTray(0, TL_TOPRIGHT, false);
    gameUI->addedLabelToTary(0, TL_TOPRIGHT, "time", "Time: 0", 150);

    //Creating Reset UI
    Application::GetInstance()->addInputListener(gameUI->addedTrayMgr("ButtonInterface", false));
    gameUI->addedButtonToTray(1, TL_CENTER, "reset", "Reset", 100);

}


