#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
class BuoyancyForceGenerator: public ForceGenerator
{
public:
	BuoyancyForceGenerator(float d, Vector3 pos) :ForceGenerator() {_liquid_density = d; _liquid_particle = new Particle(pos , { 0,0,0 }, 0, 1e6, Particle::BOX, {25,0.1,5},{0,0,255,1});};

	virtual void updateForce(Particle* particle, double t);

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

