#pragma once
#ifndef GOAL_H
#define GOAL_H

#include "Ogre.h"

class Goal
{
public:
	Goal(Ogre::SceneManager* scMgr, Ogre::SceneNode* SceneNode, Ogre::Vector3 spawnPosition);
	~Goal() {};

	Ogre::AxisAlignedBox GetWorldAABB();
private:
	Ogre::SceneManager* mSceneManager;
	Ogre::SceneNode* mSceneNode;
	Ogre::Entity* mEntity;
	
};


#endif