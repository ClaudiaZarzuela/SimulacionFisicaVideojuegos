#pragma once
#include "SolidoRigido.h"
class Button
{
public:
	enum Functions {
		STARTGAME = 0, LEVEL_1 = 1, LEVEL_2 = 2, LEVEL_3 = 3, LEVEL_4 = 4
	};
private:
	SolidoRigido* button;

public:
	Button(PxScene* gS, PxPhysics* gP, physx::PxTransform pos, float width, float height) {
		button = new SolidoRigido(gS, gP, pos, { width, height, 1 }, { 0.8,0.8,0.8,1 });
	}
};

