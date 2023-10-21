#pragma once
#include <time.h>
#include "core.hpp"
#include "Particle.h"
#include <random>
#include <list>
class ParticleGenerator
{
public:
	ParticleGenerator();
	~ParticleGenerator(){};
	virtual std::list<Particle*> generateParticles() = 0;
	inline void setOrigin(const Vector3& p) { _origin = p; }
	inline void setMeanVelocity(const Vector3& v) {_mean_velocity = v;}
	inline Vector3 getMeanVelocity() const {return _mean_velocity;}
	inline void setMeanDuration(double new_duration) {_model_particle->time = new_duration;}
	inline void setParticle(Particle* p, bool modify_pos_vel = true) {
		delete _model_particle;
		_model_particle = p->clone();
		if (modify_pos_vel) {
			_origin = p->_pose.p;
			_mean_velocity = p->_vel;
		}
		_model_particle->setPos({ -1000.0f, -1000.0f, -1000.0f });
	}
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

