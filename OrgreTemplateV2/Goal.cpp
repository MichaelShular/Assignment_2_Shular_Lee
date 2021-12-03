#include "Goal.h"
/// The defualt conconstructor use to initialize goal variables
/// 
/// @param: a Oger::SceneManager
/// @param: a Oger::SceneNode
/// @param: a Oger::Vector3 used to set player spawn Positions 
Goal::Goal(Ogre::SceneManager* scMgr, Ogre::SceneNode* SceneNode, Ogre::Vector3 spawnPosition)
{
    this->mSceneManager = scMgr;
    mSceneNode = SceneNode;
    this->mEntity = mSceneManager->createEntity("cube.mesh");
    mEntity->setCastShadows(false);

    mEntity->setMaterialName("Examples/Finish");

    mSceneNode = mSceneManager->createSceneNode("goal");
    mSceneNode->attachObject(mEntity);
    mSceneManager->getRootSceneNode()->addChild(mSceneNode);

    mSceneNode->setPosition(spawnPosition);

    mSceneNode->setScale(1.0f, 0.005f, 0.05f);
}

/// Get goal's world AABB box. 
/// 
/// The goal's AABB box will be used to check if it collides with doodle
///@returns Oger::AxisAlignedBox
Ogre::AxisAlignedBox Goal::GetWorldAABB()
{
	return mSceneNode->_getWorldAABB();
}
