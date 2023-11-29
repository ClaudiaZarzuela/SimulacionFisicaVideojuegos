#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class GravityForceGenerator : public ForceGenerator
{
public:
	GravityForceGenerator(const Vector3& g){ setGravity(g); _name = "GRAVITY";}
	virtual void updateForce(Particle* particle, double t);
	inline void setGravity(Vector3 g) { _gravity = g; }
	virtual inline void activateForce() override {
		active = !active;
		if (active) {
			std::cout << "GRAVITY FORCE: ACTIVATED" << std::endl;
		}
		else {
			std::cout << "GRAVITY FORCE: DEACTIVATED" << std::endl;
		}
	}
protected:
	Vector3 _gravity;

};