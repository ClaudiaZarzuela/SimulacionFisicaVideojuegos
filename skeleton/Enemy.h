#pragma once
#include "SolidoRigido.h"

//Clase que actua como identificador de enemigos. Un enemigo puede ser un solido rígido, dinámico o estático de cualquier forma, rojo (o blanco si se trata del suelo)
class Enemy : public SolidoRigido
{
public:
	Enemy(PxScene* gS, PxPhysics* gP, physx::PxTransform Pos, Vector3 scale, double d, float Mass, Vector4 color = {1,0,0,1}, std::string shape = "BOX", float time = -1e10) :
		SolidoRigido(gS, gP, Pos, { 0,0,0 }, { 0,0,0 }, scale, d, Mass, color, time, shape, "ENEMY") {
	}
	Enemy(PxScene* gS, PxPhysics* gP, physx::PxTransform Pos, Vector3 scale, Vector4 color = { 1,1,1,1 }) :
		SolidoRigido(gS, gP, Pos,  scale, color, "BOX", "ENEMYFLOOR") {
	}

	//Destructora vacía ya que no se tiene referencia al enemigo, se encarga el LevelSystem
	virtual ~Enemy() {}
};

