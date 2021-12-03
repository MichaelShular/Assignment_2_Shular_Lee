#include "Doodle.h"
#include "Physics.h"

/// The defualt conconstructor use to initialize doodle variables
/// 
/// @param: a Oger::SceneManager
/// @param: a Oger::SceneNode
/// @param: a Oger::Vector3 used to set player spawn Positions 
Doodle::Doodle(Ogre::SceneManager* scMgr, SceneNode* SceneNode, Ogre::Vector3 spawnPosition)
{
    this->mSceneManager = scMgr;
    mSceneNode = SceneNode;
    Ogre::Entity* ent = mSceneManager->createEntity("Entity1", "Sinbad.mesh");
    mSceneNode->attachObject(ent);
    mSceneNode->setPosition(Ogre::Vector3(spawnPosition.x, spawnPosition.y + 1, spawnPosition.z));
    spawnLocation = spawnPosition;
    mSceneNode->setScale(0.1f, 0.1f, 0.1f);
    counter = 0;
    isFalling = true;
    showReset = false;    
}

/// Get doodle's world AABB box. 
/// 
/// The doodle's AABB box will be used to check if it collides with other objects
///@returns Oger::AxisAlignedBox
AxisAlignedBox Doodle::GetWorldAABB()
{
    return mSceneNode->_getWorldAABB();
}

/// Set isFalling  
/// 
/// Used to control if doodle in game will move upwards or downwards
/// @param: a bool
void Doodle::setIsFalling(bool a)
{
    isFalling = false;
}

/// Get isFalling
/// 
///@returns a bool
bool Doodle::getIsFalling()
{
    return isFalling;
}

/// Used to get the position of the doodle.
/// 
/// @returns a Ogre::Vector3.
Ogre::Vector3 Doodle::GetPosition()
{
    return mSceneNode->getPosition();
}

/// Reset doodle
/// 
/// Used change doodle's variables so game can be player again 
/// @param: Ogre::Vector3 where the player will spawn on reset
void Doodle::resetPosition(Ogre::Vector3 spawnPosition)
{
    mSceneNode->setPosition(spawnPosition);
    apexHeight = 0;
    showReset = false;
}

/// Controls what happen during doodle's update
/// 
/// @param: a Ogre::Vector3 used to game's gravity to doodle 
/// @param: a float used to check if doodle is below a certain from the camera 
void Doodle::Update(Vector3 gravity, float cameraY)
{
    //if gravity is applied to doodle of is bounching up
    if (isFalling) 
    {
        mSceneNode->translate(gravity);
    }
    else
    {
        counter++;
        mSceneNode->translate(Vector3(0.0, 0.1, 0));
        //check if doodle need to go back to falling
        if (counter > 75) {
            isFalling = true;
            counter = 0;
            apexHeight = GetPosition().y;
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
    //Check if doodle lost
    if ( GetPosition().y < (cameraY - 14)) {
        showReset = true;
    }
}
/// Returns the maximum height doodle has reached in his jump
/// 
///@returns a float
float Doodle::getApexHeight()
    {
        return apexHeight;
    }


