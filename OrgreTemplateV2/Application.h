#pragma once
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include <OgreCompositorManager.h>
#include <iostream>
#include "Platform.h"
#include "Doodle.h"

using namespace Ogre;
using namespace OgreBites;
/// This class is used to control the start of the application and logic flow with in the application
class Application
	: public ApplicationContext
	
{
protected:
	/// The defualt conconstructor
	Application() : ApplicationContext("Assignment_2_ShularLee") {}
	static Application* app;

public:
	void operator=(const Application&) = delete;
	/// Used to get a single instance of the application class
	/// 
	/// @returns the created Application.
	static Application* GetInstance() 
	{
		if (app == nullptr) {
			app = new Application;
		}
		return app;
	}
	
	int Run();	
	bool& Running();
	void setup();
	void Wake();
	void Sleep();
	void HandleEvents();
	bool Update();	
	void Clean();
	void setIsRunning(bool a) {m_running = a; }
private:
	Ogre::Timer timer;
	Ogre::SceneNode* SinbadNode;
	bool m_running;
	Root* mRoot;
	int m_start, m_end, m_delta, m_fps;
	Camera* mCamera;
	SceneManager* mScnMgr;
	RenderWindow* mWindow; 	
	SceneNode* mCamNode;
};

#endif //_APPLICATION_H_

