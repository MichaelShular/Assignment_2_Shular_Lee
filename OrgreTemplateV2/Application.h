#pragma once
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include <OgreCompositorManager.h>
#include <iostream>

using namespace Ogre;
using namespace OgreBites;

class Application
	: public ApplicationContext
	,public InputListener
{
protected:
	Application();
	static Application* app;
public:
	int Run();
	static Application* GetInstance();
	bool& Running();
private:
	Application(Application& other) = delete;	
	void operator=(const Application&) = delete;
	bool m_running;
	Root* mRoot;
	Camera* mCamera;
	SceneManager* mSceneMgr;
	RenderWindow* mWindow;
	/*Ogre::String mResourcesCfg;
	Ogre::String mPluginsCfg;*/
protected:	
	bool Init();
	void Wake();
	void Sleep();
	void HandleEvents();
	void Update();
	void Render();
	void Clean();

};

#endif //_APPLICATION_H_

