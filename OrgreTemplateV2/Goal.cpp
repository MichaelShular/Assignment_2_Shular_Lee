#include "Goal.h"

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

Ogre::AxisAlignedBox Goal::GetWorldAABB()
{
	return mSceneNode->_getWorldAABB();
}
