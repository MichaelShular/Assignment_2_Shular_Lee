#include "Platform.h"

#include <iostream>

Platform::Platform(Ogre::SceneManager* scMgr, SceneNode* SceneNode, Ogre::Vector3 lastPlatformPosition, String id)
{
    this->mSceneManager = scMgr;
    mSceneNode = SceneNode;
    this->mEntity = mSceneManager->createEntity("cube.mesh");
    mEntity->setCastShadows(false);
    mSceneNode = mSceneManager->createSceneNode("platform" + id);
    mSceneNode->attachObject(mEntity);
    mSceneManager->getRootSceneNode()->addChild(mSceneNode);
    
    //finding spawn location 
    SpawnPos = setPlatformLevel(lastPlatformPosition);
    mSceneNode->setPosition(SpawnPos);
    
    mSceneNode->setScale(0.02f, 0.005f, 0.05f);
}

Ogre::Vector3 Platform::setPlatformLevel(Ogre::Vector3 lastPlatformPosition)
{
    float xPos, yPos;
    xPos =  Ogre::Math::RangeRandom(-14, 14);
    yPos = lastPlatformPosition.y + Ogre::Math::RangeRandom(0, 3);
    return Ogre::Vector3(xPos, yPos, 0.0);
}

Ogre::Vector3 Platform::GetPosition()
{
    return mSceneNode->getPosition();
}

