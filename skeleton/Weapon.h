#pragma once
#include "Particle.h"
#include "RenderUtils.hpp"

class Weapon
{
public:
	enum Types {
		PISTOL, ARTILLERY, FIREBALL, LASER
	};
private:
	
	Vector3 calculateGravity(Vector3 dir);
	float calculateMass(Vector3 dir);
	
	float masaReal, speedReal, speedSim, lifeTime;

public:
	Weapon(Types currentType);
	Particle* shoot(Vector3 dir, Vector3 pos);
};

