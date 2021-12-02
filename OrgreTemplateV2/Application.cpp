#include "Application.h"
#include "Game.h"
using namespace std;
using namespace Ogre;
using namespace OgreBites;

Application* Application::app = nullptr;;
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
Application* Application::GetInstance()
{
    if (app == nullptr)
    {
        app = new Application();
    }
    return app;
}

bool Application::Init()
{
    initApp();
    cout << "Initializing game" << endl;
    ApplicationContext::setup();   
    // get a pointer to the already created root
    addInputListener(this);
    mRoot = getRoot();
    mSceneMgr = mRoot->createSceneManager();
    m_running = true;
    
    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(mSceneMgr);
    Game* game = Game::GetInstance(mRoot, mSceneMgr);
    game->setup();
    return true;
}





Application::Application() : ApplicationContext("Assignment_2_ShularLee")
{
}

int Application::Run()
{   
    Init();
    while (m_running)
    {
        Wake();
        //HandleEvents();
        Update();
        if (m_running)
            Sleep();
    }
    Clean();
    return 0;
}

bool& Application::Running()
{
    return m_running;
}




void Application::Wake()
{
}

void Application::Sleep()
{

}

void Application::HandleEvents()
{
}

void Application::Update()
{
    
}

void Application::Render()
{
}

void Application::Clean()
{
}
