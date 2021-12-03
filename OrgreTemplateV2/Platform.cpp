#include "Platform.h"
#include <iostream>

Platform::Platform(Ogre::SceneManager* scMgr, SceneNode* SceneNode, Ogre::Vector3 lastPlatformPosition, String id)
{
    this->mSceneManager = scMgr;
    mSceneNode = SceneNode;
    this->mEntity = mSceneManager->createEntity("cube.mesh");
    mEntity->setCastShadows(false);

    mEntity->setMaterialName("Examples/BumpyMetal");

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
    //xPos = (rand() + 5);
    yPos = lastPlatformPosition.y + Ogre::Math::RangeRandom(0, 3);
    //yPos = 1;
    return Ogre::Vector3(xPos, yPos, 0.0);
}

Ogre::Vector3 Platform::GetPosition()
{
    return mSceneNode->getPosition();
}

void Platform::MoveRight()
{

    if (mSceneNode->getPosition().x < 65 - 10)
        mSceneNode->translate(Vector3(0.9f, 0.0f, 0.0f));
}

AxisAlignedBox Platform::GetWorldAABB()
{
    return mSceneNode->_getWorldAABB();
}

void Platform::setNewPostion(float lastPlatformPostionY)
{
    float xPos, yPos;
    xPos = Ogre::Math::RangeRandom(-14, 14);
    yPos = lastPlatformPostionY + Ogre::Math::RangeRandom(0, 3);
    mSceneNode->setPosition(Vector3(xPos, yPos, 0));
}

void Platform::resetPlaformPosition(Ogre::Vector3 lastPlatformPosition)
{
    float xPos, yPos;
    xPos = Ogre::Math::RangeRandom(-14, 14);
    //xPos = (rand() + 5);
    yPos = lastPlatformPosition.y + Ogre::Math::RangeRandom(0, 3);
    //yPos = 1;
    mSceneNode->setPosition(Vector3(xPos, yPos, 0));
}
