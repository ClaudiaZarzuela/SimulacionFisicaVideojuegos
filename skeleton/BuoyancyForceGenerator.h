#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
class BuoyancyForceGenerator: public ForceGenerator
{
public:
	//BuoyancyForceGenerator(float d, Vector3 pos) :ForceGenerator() {_liquid_density = d; _liquid_particle = new Particle(pos , { 0,0,0 }, 0, 1e6, Particle::BOX, {300,1,45},{0.2,0.2,0.5,1});}
	BuoyancyForceGenerator(float d, Vector3 pos) :ForceGenerator() {_liquid_density = d; _liquid_particle = new Particle(pos , { 0,0,0 }, 0, 1e6, Particle::BOX, {300,1,45}, Vector4(0,0, (rand() % 128 + 128) / 255.0f, 1));}

	virtual void updateForce(Entity* particle, double t);

	virtual ~BuoyancyForceGenerator() { delete(_liquid_particle); };
	virtual inline void activateForce() override {
		active = !active;
		if (active) {
			std::cout << "BUOYANCY FORCE: ACTIVATED" << std::endl;
		}
		else {
			std::cout << "BUOYANCY FORCE: DEACTIVATED" << std::endl;
		}
	}

protected:
	float _liquid_density;
	float _gravity = 9.8;

	Particle* _liquid_particle;
};

