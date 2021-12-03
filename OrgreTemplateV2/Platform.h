#pragma once
#ifndef PLATFORM_H
#define PLATFORM_H

#include "Ogre.h"

using namespace Ogre;
/// This class is used to create and control aspects the object ball.
class Platform {
public:
	Platform(Ogre::SceneManager* scMgr, SceneNode* SceneNode, Ogre::Vector3 lastPlatformPosition, String id);
	~Platform() {};

	Ogre::Vector3 GetPosition();
	void MoveRight();
	AxisAlignedBox GetWorldAABB();
	void setNewPostion(float lastPlatformPostionY);

private:
	Ogre::Vector3 setPlatformLevel(Ogre::Vector3 lastPlatformPosition);
	Ogre::Vector3 SpawnPos;
	SceneManager* mSceneManager;
	SceneNode* mSceneNode;
	Entity* mEntity;

};


#endif