#pragma once
#include "SpringForceGenerator.h"

class ElasticForceGenerator : public SpringForceGenerator
{
public:
	ElasticForceGenerator(double k, double resting_length, Particle* other):SpringForceGenerator(k, resting_length, other) { };
	~ElasticForceGenerator() {};
	virtual void updateForce(Particle* particle, double t);
};

