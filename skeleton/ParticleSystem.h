#pragma once
#include "Particle.h"
#include "ParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "FireworkGenerator.h"
#include <list>
class ParticleSystem
{
protected:
	std::list<Particle*> _particles;
	std::list <ParticleGenerator*> _particle_generators;
	FireworkGenerator* _firework_generator; // This generator is only to shoot the firework!
	Vector3 _gravity;
	
	std::vector<Firework*> _firework_pool; // Fireworks to be used as models!
	//! This is used currently in the Fireworks to spread more Fireworks!
	void onParticleDeath(Particle* p);
	void createFireworkSystem();

public:
	void integrate(double t);
	ParticleSystem(const Vector3& g = { 0.0f, -10.0f, 0.0f });
	~ParticleSystem();
	// Method to generate a Firework with the appropiate type
	void generateFirework(unsigned firework_type);
	ParticleGenerator* getParticleGenerator(const std::string& n){};
	void shootFirework();

};

