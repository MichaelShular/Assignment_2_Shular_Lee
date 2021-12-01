#include "Doodle.h"
#include "Physics.h"

Doodle::Doodle(Ogre::SceneManager* scMgr, SceneNode* SceneNode, Ogre::Vector3 spawnPosition)
{
    this->mSceneManager = scMgr;
    mSceneNode = SceneNode;
    /*this->mEntity = mSceneManager->createEntity("Sinbad.mesh");
    mEntity->setCastShadows(false);
    mSceneNode = mSceneManager->createSceneNode("doodle");
    mSceneNode->attachObject(mEntity);
    mSceneManager->getRootSceneNode()->addChild(mSceneNode);*/

    
    Ogre::Entity* ent = mSceneManager->createEntity("Entity1", "Sinbad.mesh");
    //ent->setMaterial(Ogre::MaterialManager::getSingleton().getByName("MyMaterial18"));
    mSceneNode->attachObject(ent);


    mSceneNode->setPosition(Ogre::Vector3(spawnPosition.x, spawnPosition.y + 1, spawnPosition.z));
    spawnLocation = spawnPosition;
    mSceneNode->setScale(0.1f, 0.1f, 0.1f);
    counter = 0;
    isFalling = true;
    showReset = false;
    
}

AxisAlignedBox Doodle::GetWorldAABB()
{
    return mSceneNode->_getWorldAABB();
}

void Doodle::setIsFalling(bool a)
{
    isFalling = false;
}

bool Doodle::getIsFalling()
{
    return isFalling;
}

Ogre::Vector3 Doodle::GetPosition()
{
    return mSceneNode->getPosition();
}

void Doodle::resetPosition()
{
    mSceneNode->setPosition(Ogre::Vector3(spawnLocation.x, spawnLocation.y + 1, spawnLocation.z));
    showReset = false;
}


void Doodle::Update(Vector3 gravity)
{

    if (isFalling) {
        mSceneNode->translate(gravity);
    }
    else
    {
        counter++;
        mSceneNode->translate(Vector3(0.0, 0.1, 0));
        if (counter > 75) {
            isFalling = true;
            counter = 0;
        }
    }
    //Used to change doodle to other side
    if (GetPosition().x > 14 || GetPosition().x < -14) {
        int sign = 1;
        if (GetPosition().x > 14) {
            sign = -1;
        }
        mSceneNode->setPosition((GetPosition().x + sign) * -1, GetPosition().y, GetPosition().z);
    }

    if (GetPosition().y > 10 || GetPosition().y < - 14) {
        showReset = true;
    }

}




