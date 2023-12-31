#pragma once
#include <time.h>
#include "core.hpp"
#include <random>
#include <list>
using namespace physx;
class Entity;
class Particle;
class SolidoRigido;
class ParticleGenerator
{
public:
	ParticleGenerator(PxScene* gS = nullptr, PxPhysics* gP = nullptr);
	~ParticleGenerator(){};
	virtual std::list<Entity*> generateParticles() = 0;
    bool hasPassedTimeRequired(){ return time >= maxTime;}
    bool canGenerateMoreParticles(){ return _n_particles <= _n_maxParticles;}
	virtual std::list<Entity*> generateRigidBodies() = 0;
	void setParticle(Particle* p);
	inline void setNParticles(int n_p) { _n_particles = n_p; }
	inline void updateTime(float t) { time += t; }

protected:
	int _n_particles = 1; 
	Particle* _model_particle = nullptr; 
	SolidoRigido* _model_rigidbody = nullptr; 
	std::random_device rd{};
	std::mt19937 _mt{rd()};
	PxScene* gScene = nullptr;
	PxPhysics* gPhysics = nullptr;
	int _n_maxParticles = 50;
	float time = 0;
	float maxTime = 0.1;
};

