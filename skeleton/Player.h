#pragma once
#include "SolidoRigido.h"
#include <iostream>

//Clase que actua como identificador del jugador. Este es  un solido r�gido din�mico de cualquier forma amarillo.
class Player: public SolidoRigido
{
public:
	Player(PxScene* gS, PxPhysics* gP, physx::PxTransform Pos, Vector3 scale, double d, float Mass,  std::string tShape = "BOX", Vector4 color = { 255,255,0,1 },float time = -1e10):
	SolidoRigido(gS, gP, Pos, {0,0,0},{0,0,0}, scale, d ,Mass, color, time, tShape){}

	virtual ~Player(){}

};

