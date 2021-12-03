#include "Application.h"
#include "Game.h"

using namespace std;
using namespace Ogre;
using namespace OgreBites;
#define FPS 60
Application* Application::app = nullptr;;

void Application::setup()
{    
    ApplicationContext::setup();    
    
    // get a pointer to the already created root
    mRoot = getRoot();
    mScnMgr = mRoot->createSceneManager();
    m_running = true;
    m_fps = FPS;
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
    m_start = timer.getMicroseconds();
}

void Application::Sleep()
{   
    m_end = timer.getMicroseconds();
    m_delta = m_end - m_start;    
    if (m_delta < m_fps) // Engine has to sleep.
        std::this_thread::sleep_for(std::chrono::milliseconds(m_fps - m_delta));

    timer.reset();
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
