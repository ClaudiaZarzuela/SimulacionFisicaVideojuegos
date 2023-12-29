#pragma once
#include "SolidoRigido.h"
#include <iostream>
class Player: public SolidoRigido
{
public:
	Player(PxScene* gS, PxPhysics* gP, physx::PxTransform Pos, Vector3 scale, double d, float Mass, Vector4 color = {0.5,0.5,1,0.5}, float time = -1e10):
	SolidoRigido(gS, gP, Pos, {0,0,0},{0,0,0}, scale, d ,Mass, color, time){
	}

	virtual ~Player(){}

};

