#pragma once
#include "Particle.h"
#include "ParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include <list>
class ParticleSystem
{
protected:
	std::list<Particle*> _particles;
	std::list <ParticleGenerator*> _particle_generators;
	Vector3 _gravity;
	

public:
	void integrate(double t);
	ParticleSystem(const Vector3& g = { 0.0f, -10.0f, 0.0f });
	~ParticleSystem(){};
	ParticleGenerator* getParticleGenerator(const std::string& n){};

};

