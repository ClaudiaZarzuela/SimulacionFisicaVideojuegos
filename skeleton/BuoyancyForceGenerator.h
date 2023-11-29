#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
class BuoyancyForceGenerator: public ForceGenerator
{
public:
	BuoyancyForceGenerator(float h, float v, float d) :ForceGenerator() { _height = h; _volume = v; _liquid_density = d; };

	virtual void updateForce(Particle* particle, double t);

	virtual ~BuoyancyForceGenerator();
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
	float _height;
	float _volume;
	float _liquid_density;
	float _gravity = 9.8;

	Particle* _liquid_particle;
};

