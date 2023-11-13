#pragma once
#include "Particle.h"
#include "ParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "FireworkGenerator.h"
#include <list>
#include "GravityForceGenerator.h"
#include "ParticleForceRegistry.h"
class ParticleSystem
{
private:
	struct BoundingBox {
		int minX, maxX;
		int minY, maxY;
		int minZ, maxZ;
	};
	BoundingBox box;
	void inicialiceBoundingBox();
	bool insideBoundingBox(Vector3 pos);

	Vector3 _gravity;
	std::list<Particle*> _particles;
	std::list <ParticleGenerator*> _particle_generators;
	std::list <ForceGenerator*> _force_generators;
	FireworkGenerator* _firework_generator = nullptr; 
	ParticleForceRegistry* _force_registry = nullptr;
	GravityForceGenerator* gravity_generator = nullptr;
	void onParticleDeath(Particle* p);

public:
	void integrate(double t);
	ParticleSystem(const Vector3& g = { 0.0f, -10.0f, 0.0f });
	~ParticleSystem();
	void shootFirework();
	void createGenerators();
	void createForceGenerators();
	void registerForces();

};

