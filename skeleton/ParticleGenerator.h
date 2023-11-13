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
	~ParticleGenerator() {};
	virtual std::list<Particle*> generateParticles() = 0;
	inline void setOrigin(const Vector3& p) { _origin = p; }
	inline void setMeanVelocity(const Vector3& v) {_mean_velocity = v;}
	inline Vector3 getMeanVelocity() const {return _mean_velocity;}
	void setMeanDuration(double new_duration);
	void setParticle(Particle* p);
	inline void setNParticles(int n_p) { _n_particles = n_p; }

protected:
	int _n_particles = 1; // Number of particles for each generateParticles call(TODO: add randomness ? ? )
	double _generation_prob = 1.0; // IF 1.0 --> always produces particles
	Particle* _model_particle = nullptr; // Has the attributes of the particle that will be generated!(damping, lifetime, etc.)
	Vector3 _origin, _mean_velocity;
	std::random_device rd{};
	std::mt19937 _mt{rd()}; //generador de numeros aleatorios
	std::string _name;
};

