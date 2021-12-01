#pragma once
#ifndef PHYSICS_H
#define PHYSICS_H

#include "Ogre.h"


using namespace Ogre;


class Physics {
protected:
    Physics() {};
	~Physics() {};

    static Physics* physics_;
public:
    Physics(Physics& other) = delete;
    void operator=(const Physics&) = delete;

    static Physics* GetInstance();
	bool checkAAABB(AxisAlignedBox a, AxisAlignedBox b);
    void setGravity(Vector3 newGravity);
    Vector3 getGravity();
private:
    Vector3 gravity;
};

#endif