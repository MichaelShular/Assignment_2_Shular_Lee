#include "Application.h"
#include "Game.h"

using namespace std;
using namespace Ogre;
using namespace OgreBites;
#define FPS 60
Application* Application::app = nullptr;;

/// Initialize the class's variables and create an Instance of the game.
/// 
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
    //Set up scene and camera from the game
    Game* game = Game::GetInstance(mRoot, mScnMgr, mCamera);
    game->setup();   
}

///Makes a routine for the application until application is done running
/// 
/// @returns an int
int Application::Run()
{     
   
    while (m_running)
    {        
        Wake();        
        Update();
        if (m_running)
            Sleep();
    }
    Clean();
    return 0;
}

///Check if application is still updating
/// 
/// @returns bool
bool& Application::Running()
{
    return m_running;
}

///Set the start time
/// 
///Setting the time for when the next frame is started within function Application::Run 
void Application::Wake()
{
    m_start = timer.getMicroseconds();
}

/// Lock the FPS
/// 
/// Used to lock the appliaction to a consistent frame rate bewteen updates  
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

///Game Update
/// 
/// Updates one frame of the game instance 
/// @returns bool
bool Application::Update()
{    
    // Update Game renderOneFrame
    Game* game = Game::GetInstance(mRoot, mScnMgr, mCamera);
    game->renderOneFrame();
    return true;
}

void Application::Clean()
{

}
