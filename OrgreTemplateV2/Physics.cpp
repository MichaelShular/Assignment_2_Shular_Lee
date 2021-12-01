#include "Physics.h"

Physics* Physics::physics_ = nullptr;;

Physics* Physics::GetInstance()
{
    
    if (physics_ == nullptr) {
        physics_ = new Physics();
    }
    return physics_;
}

bool Physics::checkAAABB(AxisAlignedBox a, AxisAlignedBox b)
{
	return a.intersects(b);
}

void Physics::setGravity(Vector3 newGravity)
{
    gravity = newGravity;
}

Vector3 Physics::getGravity()
{
    return gravity;
}



