#include "Application.h"
#include "Game.h"
using namespace std;
using namespace Ogre;
using namespace OgreBites;

Application* Application::app = nullptr;;

void Application::setup()
{    
    ApplicationContext::setup();    
    addInputListener(this);

    // get a pointer to the already created root
    mRoot = getRoot();
    mScnMgr = mRoot->createSceneManager();
    m_running = true;

    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(mScnMgr);
    Game* game = Game::GetInstance(mRoot, mScnMgr, mCamera);
    
   
}


int Application::Run()
{   
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
    Game* game = Game::GetInstance(mRoot, mScnMgr, mCamera);
    game->Update();
}

void Application::Render()
{
}

void Application::Clean()
{
}
