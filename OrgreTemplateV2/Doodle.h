#pragma once
#ifndef DOODLE_H
#define DOODLE_H

#include "Ogre.h"

using namespace Ogre;
/// This class is used to create and control aspects the object ball.
class Doodle {
public:
	Doodle(Ogre::SceneManager* scMgr, SceneNode* SceneNode);
	~Doodle() {};



private:
	SceneManager* mSceneManager;
	SceneNode* mSceneNode;
	Entity* mEntity;

};







#endif