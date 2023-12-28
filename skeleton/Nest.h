#pragma once
#include "InteractuableObject.h"
#include "SolidoRigido.h"

class Nest : public InteractuableObject
{
private:
	SolidoRigido* floor = nullptr;
	float floorWidth = 20;
	float floorLength = 5/2;
	float floorHeight = 2.5/2;
	float wallsHeight = 10/2;
	float wallsWidth = 2.5;

	SolidoRigido* right = nullptr;
	SolidoRigido* left = nullptr;
	SolidoRigido* centro = nullptr;

public:
	Nest(PxScene* gS, PxPhysics* gP, physx::PxTransform pos): 
		InteractuableObject({ pos.p.x , pos.p.y + floorHeight + wallsHeight / 2 , pos.p.z }, wallsHeight, floorWidth - wallsWidth, floorLength) {
		floor = new SolidoRigido(gS, gP, pos, { floorWidth, floorHeight, floorLength }, { 0.5,1,0.5,1 });
		physx::PxTransform posRight = { pos.p.x + floorWidth , pos.p.y + floorHeight + wallsHeight/2 , pos.p.z };
		physx::PxTransform posLeft = { pos.p.x - floorWidth , pos.p.y + floorHeight + wallsHeight / 2 , pos.p.z };
		right = new SolidoRigido(gS, gP, posRight, { wallsWidth, wallsHeight, floorLength }, { 0.5,1,0.5,1 });
		left = new SolidoRigido(gS, gP, posLeft, { wallsWidth, wallsHeight, floorLength }, { 0.5,1,0.5,1 });

	}
};

