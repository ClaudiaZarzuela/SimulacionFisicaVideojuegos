#pragma once
#include <ctype.h>
#include <PxPhysicsAPI.h>
#include <vector>
#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "PxSceneDesc.h"

using namespace physx;
class MyItem
{
private:
	PxMaterial* _material;
	PxShape* _shape;
	PxRigidActor* _item;
	RenderItem* renderItem = nullptr;

	void tuneBox();

public:
	MyItem(bool ground, float pX, float pY, float pZ, float sX, float sY, float sZ,
		float staticFriction, float dynamicFriction, float restitution, PxScene* gScene, PxPhysics* gPhysics);
	~MyItem();

};

