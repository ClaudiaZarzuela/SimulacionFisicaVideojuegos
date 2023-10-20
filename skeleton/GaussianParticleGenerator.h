#pragma once
#include "ParticleGenerator.h"
class GaussianParticleGenerator: public ParticleGenerator
{
public:
	GaussianParticleGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel);
	virtual std::list<Particle*> generateParticles(){};

protected:
	Vector3 _std_dev_pos, _std_dev_vel;
	std::normal_distribution<double> d{ 0,1 };
};

