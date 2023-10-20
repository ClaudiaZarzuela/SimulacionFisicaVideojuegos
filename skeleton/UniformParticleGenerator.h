#pragma once
#include "ParticleGenerator.h"
class UniformParticleGenerator :public ParticleGenerator
{
public: 
	UniformParticleGenerator(Vector3 pos, Vector3 vel, double iMass);
	virtual std::initializer_list<Particle*> generateParticle();

protected:
	Vector3 _pos, _vel;
	double _iMass;
};

