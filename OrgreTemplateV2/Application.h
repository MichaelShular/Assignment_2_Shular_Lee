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

class Application
	: public ApplicationContext
	
{
protected:
	Application() : ApplicationContext("Assignment_2_ShularLee") {}
	static Application* app;

public:
	void operator=(const Application&) = delete;
	

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
	void Render();
	void Clean();
private:
	Ogre::SceneNode* SinbadNode;
	bool m_running;
	Root* mRoot;
	
	Camera* mCamera;
	SceneManager* mScnMgr;
	RenderWindow* mWindow; 	
	SceneNode* mCamNode;
	Platform* plaform[9];
	Doodle* doodle;
	/*Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;*/
private:
	

};

#endif //_APPLICATION_H_

