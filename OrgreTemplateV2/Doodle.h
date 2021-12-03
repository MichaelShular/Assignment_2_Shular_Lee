#pragma once
#ifndef DOODLE_H
#define DOODLE_H

#include "Ogre.h"
#include "Physics.h"

using namespace Ogre;
/// This class is used to create and control aspects the object ball.
class Doodle {
public:
	Doodle(Ogre::SceneManager* scMgr, SceneNode* SceneNode, Ogre::Vector3 spawnPosition);
	~Doodle() {};
	AxisAlignedBox GetWorldAABB();
	void setIsFalling(bool a);
	bool getIsFalling();
	
	Ogre::Vector3 GetPosition();
	void resetPosition(Ogre::Vector3 spawnPosition);
	bool Goal(float d);
	void Update(Vector3 gravity, float cameraY);
	float getApexHeight();
	
	bool showReset;

private:
	SceneManager* mSceneManager;
	SceneNode* mSceneNode;
	Entity* mEntity;
	bool isFalling;
	int counter;
	Ogre::Vector3 spawnLocation;
	float apexHeight;
};







#endif