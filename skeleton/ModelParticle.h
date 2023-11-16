#pragma once
#include "Particle.h"
class ModelParticle
{
public:
	struct Types {
		float masaReal, speedReal, speedSim;
	};
	struct Models {
			Types PISTOL = { 330.0f , 45.0f, 5.0f },
			ARTILLERY = { 1800.0f, 20.0f, 12.0f },
			FIREBALL = { 250.0f, 10.0f, 3.0f },
			LASER = { 300000000.0f, 100.0f, 0.1f };
	};
private:
	Vector3 calculateGravity(Types currentType, Vector3 dir);
	float calculateMass(Types currentType, Vector3 dir);

public:
	ModelParticle(){};
	//Particle* createParticle(Types currentType, float lifeTime = 20.0f);
};

