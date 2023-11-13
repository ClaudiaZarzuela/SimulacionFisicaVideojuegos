#pragma once
#include "ForceGenerator.h"
#include "core.hpp"

class GravityForceGenerator : public ForceGenerator
{
public:
	GravityForceGenerator(const Vector3& g){ setGravity(g); }
	virtual void updateForce(Particle* particle, double t) override;
	inline void setGravity(Vector3 g) { _gravity = g; }

protected:
	Vector3 _gravity;

};