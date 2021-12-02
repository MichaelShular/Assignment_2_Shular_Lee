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


void Game::setup()
{       
    Application::GetInstance()->addInputListener(this);
    createCamera();
    createScene();
    createFrameListener();
}

void Game::createScene()
{

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
            plaform[i] = new Platform(mScnMgr, SinbadNode, Ogre::Vector3(0.0f, -10.0f, 0.0f), std::to_string(i));
        }
        else
        {
            plaform[i] = new Platform(mScnMgr, SinbadNode, plaform[i - 1]->GetPosition(), std::to_string(i));
        }
    }
    //Spawning doodle
    doodle = new Doodle(mScnMgr, SinbadNode, Vector3(0,0,0));


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
    Ogre::Viewport* viewport = Application::GetInstance()->getRenderWindow()->addViewport(mCamera);
    viewport->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));
    mCamera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
}



//bool Game::mouseMoved(const MouseMotionEvent& evt)
//{
//    rotX = evt.xrel;
//    rotY = evt.yrel;
//    return true;
//}
//
bool Game::keyPressed(const KeyboardEvent& evt)
{
    switch (evt.keysym.sym)
    {
    case SDLK_ESCAPE:
       
        
        break;
    case 'w':
        translate = Ogre::Vector3(0, 10, 0);
        break;
    case 's':
        translate = Ogre::Vector3(0, -10, 0);
        break;
    case 'a':
        translate = Ogre::Vector3(-10, 0, 0);
        break;
    case 'd':
        translate = Ogre::Vector3(10, 0, 0);
        break;
    default:
        break;
    }
    return true;
}

void Game::createFrameListener()
{
    Ogre::FrameListener* FrameListener = new ExampleFrameListener(SinbadNode, mCamNode);
    mRoot->addFrameListener(FrameListener);
}

void Game::renderOneFrame()
{
    //Ogre::WindowEventUtilities::messagePump();
    mRoot->renderOneFrame();
    translate = Ogre::Vector3(-10, 0, 0);
}

Game::Game(Root* root, SceneManager* scn ,Camera* cam)
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
