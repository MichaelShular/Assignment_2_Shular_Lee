#include "Physics.h"

Physics::Physics()
{
}

bool Physics::checkAAABB(AxisAlignedBox a, AxisAlignedBox b)
{
	return a.intersects(b);
}
