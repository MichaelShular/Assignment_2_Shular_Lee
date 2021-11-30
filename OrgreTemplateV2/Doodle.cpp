#include "Doodle.h"

Doodle::Doodle(Ogre::SceneManager* scMgr, SceneNode* SceneNode)
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

    mSceneNode->setPosition(Ogre::Vector3(0.0, 1, 0.0));

    mSceneNode->setScale(0.1f, 0.1f, 0.1f);
    counter = 0;
    isFalling = true;
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

void Doodle::Update()
{
    if (isFalling) {
        mSceneNode->translate(Vector3(0.0, -0.05, 0));
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

}




