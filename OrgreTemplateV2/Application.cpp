#include "Application.h"
#include "Game.h"

using namespace std;
using namespace Ogre;
using namespace OgreBites;

Application* Application::app = nullptr;;

void Application::setup()
{    
    ApplicationContext::setup();    
    
    // get a pointer to the already created root
    mRoot = getRoot();
    mScnMgr = mRoot->createSceneManager();
    m_running = true;

    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(mScnMgr);
    Game* game = Game::GetInstance(mRoot, mScnMgr, mCamera);
    game->setup();
   
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

bool Application::Update()
{    
    Game* game = Game::GetInstance(mRoot, mScnMgr, mCamera);
    game->renderOneFrame();
    return true;
}

void Application::Render()
{
}

void Application::Clean()
{
}
