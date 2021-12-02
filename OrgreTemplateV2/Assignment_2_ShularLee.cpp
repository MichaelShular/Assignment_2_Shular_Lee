//Assignment_2_ShularLee
//Michael Shular 101273089
//Daekoen Lee 101076401

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include <OgreCompositorManager.h>
#include <iostream>
#include "Platform.h"
#include "Doodle.h"
#include "Physics.h"
#include <time.h>
#include "UI.h"
#include "OgreApplicationContext.h"
#include "Input.h"


using namespace Ogre;
using namespace OgreBites;

Ogre::Vector3 translate(0, 0, 0);
float rotX = 0.0f;
float rotY = 0.0f;
float _movementspeed;

class ExampleFrameListener : public Ogre::FrameListener
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
        //std::cout << "Frame started" << std::endl;

       /* _camNode->yaw(Ogre::Radian(rotX * _mousespeed * evt.timeSinceLastFrame));
        _camNode->pitch(Ogre::Radian(rotY * _mousespeed * evt.timeSinceLastFrame));
        rotX = 0.0f;
        rotY = 0.0f;*/
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

class Game
    : public ApplicationContext
    , public InputListener
{
private:
    SceneManager* mScnMgr;
    Root* mRoot;
    Camera* mCamera;
    SceneNode* mCamNode;
    Platform* plaform [9];
    Doodle* doodle;
    Physics* gamePhysics;
    UI* UIElements;
    Input* gameInput;
    OgreBites::TrayListener myTrayListener;
    OgreBites::TrayManager* mTrayMgr;
    OgreBites::TrayManager* mButtonTrayMgr;

    bool _keepRunning;
public:
    Game();
    virtual ~Game() {}

    void setup();
    void createScene();
    void createCamera();
    bool keyPressed(const KeyboardEvent& evt);
    bool mouseMoved(const MouseMotionEvent& e);
    void createFrameListener();
    void renderOneFrame();
    void createTrayListener();
    bool keepRunning();
    Ogre::SceneNode* SinbadNode;
};


Game::Game()
    : ApplicationContext("Assignment_2_ShularLee")
{
    _keepRunning = true;
    _movementspeed = 50.0f;
}


void Game::setup()
{
    // do not forget to call the base first
    ApplicationContext::setup();
    addInputListener(this);

    // get a pointer to the already created root
    mRoot = getRoot();
    mScnMgr = mRoot->createSceneManager();

    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(mScnMgr);
    
    //adding physics 
    gamePhysics = Physics::GetInstance();
    UIElements = UI::GetInstance(getRenderWindow(), mScnMgr, getOverlaySystem());
    gameInput = Input::GetInstance(mRoot);
    
    createCamera();
    createScene();
    createTrayListener();
    createFrameListener();
}

void Game::createScene()
{
    //Needed to generate a random seed
    srand(time(NULL));
    
    // -- tutorial section start --
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
    for (int i = 0; i < 9; i++)
    {   
        if (i == 0) {
            plaform[i] = new Platform(mScnMgr, SinbadNode, Ogre::Vector3(0.0f, -10.0f, 0.0f), std::to_string(i) ); 
        }
        else
        {
            plaform[i] = new Platform(mScnMgr, SinbadNode, plaform[i -1]->GetPosition(), std::to_string(i));
        }   
    }
    //Spawning doodle
    doodle = new Doodle(mScnMgr, SinbadNode, plaform[0]->GetPosition());
    
    gamePhysics->setGravity(Vector3(0.0f, -0.1f, 0.0f));
}

void Game::createCamera()
{

    //! [camera]
    mCamNode = mScnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    mCamera = mScnMgr->createCamera("myCam");

    mCamera->setNearClipDistance(5); // specific to this sample
    mCamera->setAutoAspectRatio(true);
    mCamNode->attachObject(mCamera);
    mCamNode->setPosition(0, 0, 25);
    mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);

    // and tell it to render into the main window
    Ogre::Viewport* viewport = getRenderWindow()->addViewport(mCamera);
    viewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));
    mCamera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
}

bool Game::mouseMoved(const MouseMotionEvent& evt)
{
    rotX = evt.xrel;
    rotY = evt.yrel;
    return true;
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

/// Used to initialize the UI class and create all trays in the scene.
void Game::createTrayListener()
{
    
    addInputListener(UIElements->addedTrayMgr("InterfaceName", true));
    UIElements->addedFrameStatsToTray(0, TL_TOPRIGHT, false);
    UIElements->addedLabelToTary(0, TL_TOPRIGHT, "time", "Time: 0", 150);

    addInputListener(UIElements->addedTrayMgr("ButtonInterface", false));
    UIElements->addedButtonToTray(1, TL_CENTER, "reset", "Reset", 100);
}

void Game::renderOneFrame()
{
    //Ogre::WindowEventUtilities::messagePump();
    doodle->Update(gamePhysics->getGravity());
    mRoot->renderOneFrame();
    
    if (gameInput->checkIfKeyBeingPressed(OgreBites::SDLK_ESCAPE)) {
        mRoot->queueEndRendering();
        _keepRunning = false;
    }
    //if (doodle->showReset == true) {
    //    UIElements->showResetButton();
    //    if (UIElements->getReset() == true) {
    //        UIElements->hideResetButton();
    //        doodle->resetPosition();
    //        //reset camra position
    //    }
    //}
    
    if (doodle->getIsFalling()) {
        for (int i = 0; i < 9; i++)
        {
            if (gamePhysics->checkAAABB(doodle->GetWorldAABB(), plaform[i]->GetWorldAABB())) {
                doodle->setIsFalling(false);
            }
        }
    }

    
}

bool Game::keepRunning()
{
    return _keepRunning;
}


int main(int argc, char** argv)
{
    try
    {
        Game app;
        app.initApp();

        //app.getRoot()->startRendering();
        while (app.keepRunning())
        {
            app.renderOneFrame();
        }
        app.closeApp();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;
}









