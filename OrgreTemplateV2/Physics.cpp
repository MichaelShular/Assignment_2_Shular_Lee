#include "Physics.h"

Physics* Physics::physics_ = nullptr;;

/// Used to get a single instance of the Physics class
/// 
/// @returns the created Physics.
Physics* Physics::GetInstance()
{
    if (physics_ == nullptr) {
        physics_ = new Physics();
    }
    return physics_;
}

/// Used to check the collision
/// 
/// This function check collision use AABB 
/// @param: a Oger::AxisAlignedBox object one
/// @param: a Oger::AxisAlignedBox object two
/// @returns a bool.
bool Physics::checkAAABB(AxisAlignedBox a, AxisAlignedBox b)
{
	return a.intersects(b);
}

/// Used to set gravity for game
/// 
/// @param: a Oger::Vector3
void Physics::setGravity(Vector3 newGravity)
{
    gravity = newGravity;
}
/// Used to get gravity for game
/// 
/// @returns Oger::Vector3
Vector3 Physics::getGravity()
{
    return gravity;
}



