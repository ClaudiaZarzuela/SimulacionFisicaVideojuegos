#pragma once
#include "SpringForceGenerator.h"

class ElasticForceGenerator : public SpringForceGenerator
{
public:
	ElasticForceGenerator(double k, double resting_length, Particle* other):SpringForceGenerator(k, resting_length, other) { };
	~ElasticForceGenerator() {};
	virtual void updateForce(Entity* particle, double t);
};

