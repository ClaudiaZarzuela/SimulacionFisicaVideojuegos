#pragma once
#include "Particle.h"
#include "RenderUtils.hpp"

class Proyectil
{
public:
	enum Types {
		PISTOL, ARTILLERY, FIREBALL, LASER
	};
private:
	Vector3 calculateGravity(Vector3 dir);
	float calculateMass(Vector3 dir);

	
	float masaReal, speedReal, speedSim, lifeTime;
    std::vector<Particle*> particles;

public:
	Proyectil(Types currentType);
	void integrate(double t);
	void shoot(Vector3 dir, Vector3 pos);
};

