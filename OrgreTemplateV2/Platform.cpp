#include "Platform.h"
#include <iostream>

/// The defualt conconstructor
/// 
/// @param: a Oger::SceneManager
/// @param: a Oger::SceneNode
/// @param: a Oger::Vector3 the position of the last platform
/// @param: a string used to create unique SceneNode 
Platform::Platform(Ogre::SceneManager* scMgr, SceneNode* SceneNode, Ogre::Vector3 lastPlatformPosition, String id)
{
    this->mSceneManager = scMgr;
    mSceneNode = SceneNode;
    this->mEntity = mSceneManager->createEntity("cube.mesh");
    mEntity->setCastShadows(false);
    //giving material 
    mEntity->setMaterialName("Examples/BumpyMetal");

    mSceneNode = mSceneManager->createSceneNode("platform" + id);
    mSceneNode->attachObject(mEntity);
    mSceneManager->getRootSceneNode()->addChild(mSceneNode);
    
    //finding and setting spawn location 
    SpawnPos = setPlatformLevel(lastPlatformPosition);
    mSceneNode->setPosition(SpawnPos);
    //Set size
    mSceneNode->setScale(0.02f, 0.005f, 0.05f);
}

/// Used to randomly set the position
/// 
/// Used the position of the last platform spawn in game
/// If the platform is the first in array just pass through positon of where to start spawning
/// @param: a Oger::Vector the position of the last platform
Ogre::Vector3 Platform::setPlatformLevel(Ogre::Vector3 lastPlatformPosition)
{
    float xPos, yPos;
    xPos =  Ogre::Math::RangeRandom(-14, 14);
    yPos = lastPlatformPosition.y + Ogre::Math::RangeRandom(0, 3);
    return Ogre::Vector3(xPos, yPos, 0.0);
}

/// Get position
/// 
/// @returns a Oger::Vector3
Ogre::Vector3 Platform::GetPosition()
{
    return mSceneNode->getPosition();
}

/// Get platform's world AABB box. 
/// 
/// The platform's AABB box will be used to check if it collides with doodle
/// @returns Oger::AxisAlignedBox
AxisAlignedBox Platform::GetWorldAABB()
{
    return mSceneNode->_getWorldAABB();
}

/// Used to move platforms above the current highest platform
/// 
/// @param: a Oger::Vector3 the position of the last platform
void Platform::setNewPostion(float lastPlatformPostionY)
{
    float xPos, yPos;
    xPos = Ogre::Math::RangeRandom(-14, 14);
    yPos = lastPlatformPostionY + Ogre::Math::RangeRandom(0, 3);
    mSceneNode->setPosition(Vector3(xPos, yPos, 0));
}

/// Reset platform
/// 
/// Used change platform postion so game can be played again
void Platform::resetPlaformPosition(Ogre::Vector3 lastPlatformPosition)
{
    float xPos, yPos;
    xPos = Ogre::Math::RangeRandom(-14, 14);
    yPos = lastPlatformPosition.y + Ogre::Math::RangeRandom(0, 3);
    mSceneNode->setPosition(Vector3(xPos, yPos, 0));
}
