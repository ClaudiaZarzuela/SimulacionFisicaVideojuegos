#pragma once
#include <time.h>
#include "core.hpp"
#include <random>
#include <list>
class Particle;
class ParticleGenerator
{
public:
	ParticleGenerator();
	~ParticleGenerator(){};
	virtual std::list<Particle*> generateParticles() = 0;
	void setParticle(Particle* p);
	inline void setNParticles(int n_p) { _n_particles = n_p; }

protected:
	int _n_particles = 1; // Number of particles for each generateParticles call(TODO: add randomness ? ? )
	Particle* _model_particle = nullptr; // Has the attributes of the particle that will be generated!(damping, lifetime, etc.)
	std::random_device rd{};
	std::mt19937 _mt{rd()}; //generador de numeros aleatorios
};

