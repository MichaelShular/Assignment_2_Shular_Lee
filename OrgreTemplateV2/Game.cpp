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

Game::Game(Root* root, SceneManager* scn, Camera* cam)
{
    mRoot = root;
    mScnMgr = scn;
    mCamera = cam;
}

Game* Game::GetInstance(Root* root, SceneManager* scn, Camera* cam)
{
    if (_game == nullptr) {
        _game = new Game(root, scn, cam);
    }
    return _game;
}

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

    //
    Entity* lightEnt = mScnMgr->createEntity("LightEntity", "sphere.mesh");
    SceneNode* lightNode = mScnMgr->createSceneNode("LightNode");
    //lightNode->attachObject(lightEnt);
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

    gamePhysics->setGravity(Vector3(0.0f, -0.1f, 0.0f));

    gameAudio->playBGM("../media/ophelia.mp3");
    gameAudio->setVolume(0.2f);
}

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

bool Game::keyPressed(const KeyboardEvent& evt)
{
    gameInput->Update(evt);
    return true;
}

void Game::createFrameListener()
{
    Ogre::FrameListener* FrameListener = new ExampleFrameListener(SinbadNode, mCamNode);
    mRoot->addFrameListener(FrameListener);
}

void Game::renderOneFrame()
{ 
    mRoot->renderOneFrame();
    
    if (doodle->showReset == true) {
        gameUI->setCaptionForLabel(0, Ogre::StringConverter::toString(mPausedTime));
        gameUI->setTrayVisibility(1, true);
        if (gameUI->getIsButtonPressed(0) == true) {
            gameUI->setTrayVisibility(1, false);
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
            //reset camra position
        }
    }
    else {
        if (gameInput->checkIfKeyBeingPressed('a'))
            translate = Ogre::Vector3(-10, 0, 0);
        if (gameInput->checkIfKeyBeingPressed('d'))
            translate = Ogre::Vector3(10, 0, 0);
        gameUI->setCaptionForLabel(0, Ogre::StringConverter::toString(timer.getMilliseconds() / 1000));
        mPausedTime = timer.getMilliseconds() / 1000; 
        doodle->Update(gamePhysics->getGravity(), mCamNode->getPosition().y);
        mCameraPostionToReach = doodle->getApexHeight();
    }
    if (gameInput->checkIfKeyBeingPressed(SDLK_ESCAPE)) {
        mRoot->queueEndRendering();
        Application::GetInstance()->setIsRunning(false);
    }
   
    /*if (doodle->Goal(plaform[8]->GetPosition().y))
    {
        Application::GetInstance()->Running() = false;
    }*/

    //Game Collision
    if (doodle->getIsFalling()) {
        for (int i = 0; i < numberOfPlatforms; i++)
        {
           
            if (plaform[i]->GetPosition().y < mCamNode->getPosition().y && std::abs(plaform[i]->GetPosition().y - mCamNode->getPosition().y) > 11) {
                plaform[i]->setNewPostion(lastPlaformHeight);
                lastPlaformHeight = plaform[i]->GetPosition().y;
            }

            if (gamePhysics->checkAAABB(doodle->GetWorldAABB(), plaform[i]->GetWorldAABB())) {
                doodle->setIsFalling(false);
                gameAudio->playSFX("../media/jump.wav");
            }
        }
    }
   

    if (mCurrentCameraPostion < mCameraPostionToReach) {
        mCamNode->lookAt(Vector3(0, mCamNode->getPosition().y + 0.05f, 0), Node::TS_WORLD);
        mCamNode->setPosition(0, mCamNode->getPosition().y + 0.1f, 25);
        mCurrentCameraPostion = mCamNode->getPosition().y;
    }



    std::cout << doodle->GetPosition().y << std::endl;
    
    
    gameInput->reset();
}



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


