#pragma once
#include "SolidoRigido.h"
class Enemy : public SolidoRigido
{
public:
	Enemy(PxScene* gS, PxPhysics* gP, physx::PxTransform Pos, Vector3 scale, double d, float Mass, Vector4 color = {1,0,0,1 }, float time = -1e10) :
		SolidoRigido(gS, gP, Pos, { 0,0,0 }, { 0,0,0 }, scale, d, Mass, color, time,"BOX", "ENEMY") {
	}
	Enemy(PxScene* gS, PxPhysics* gP, physx::PxTransform Pos, Vector3 scale, Vector4 color = { 0.05,0,0,1 }) :
		SolidoRigido(gS, gP, Pos,  scale, color, "BOX", "ENEMY") {
	}

	virtual ~Enemy() {}
};

