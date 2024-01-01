#pragma once
#include "InteractuableObject.h"
#include "SolidoRigido.h"

class Nest : public InteractuableObject
{
private:
	SolidoRigido* floor = nullptr;
	float floorWidth = 25;
	float floorLength = 10;
	float floorHeight = 1;
	float wallsHeight = 5;
	float wallsWidth = 2;

	SolidoRigido* right = nullptr;
	SolidoRigido* left = nullptr;
	SolidoRigido* centro = nullptr;

public:
	Nest(PxScene* gS, PxPhysics* gP, physx::PxTransform pos, float floorWidth = 25, float floorLength = 10, float floorHeight = 1,
		float wallsHeight = 5, float wallsWidth = 2):
		InteractuableObject({ pos.p.x , pos.p.y + (floorHeight + wallsHeight/2), pos.p.z}, wallsHeight, floorWidth - wallsWidth, floorLength) {
		floor = new SolidoRigido(gS, gP, pos, { floorWidth, floorHeight, floorLength }, { 0.5,1,0.5,1 });
		physx::PxTransform posRight = { pos.p.x + floorWidth - wallsWidth, pos.p.y + floorHeight + wallsHeight , pos.p.z };
		physx::PxTransform posLeft = { pos.p.x - floorWidth + wallsWidth, pos.p.y + floorHeight + wallsHeight , pos.p.z };
		right = new SolidoRigido(gS, gP, posRight, { wallsWidth, wallsHeight, floorLength }, { 0.5,1,0.5,1 });
		left = new SolidoRigido(gS, gP, posLeft, { wallsWidth, wallsHeight, floorLength }, { 0.5,1,0.5,1 });

	}
	virtual ~Nest() {
		delete(right);
		delete(left);
		delete(centro);
		delete(floor);
	}
};

