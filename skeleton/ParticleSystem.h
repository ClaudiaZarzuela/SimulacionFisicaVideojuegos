#pragma once
#include "Particle.h"
#include "ParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "FireworkGenerator.h"
#include <list>
#include "GravityForceGenerator.h"
#include "ParticleDragGenerator.h"
#include "ParticleForceRegistry.h"
#include "ParticleWhirlWindGenerator.h"
#include "SpringForceGenerator.h"
#include "ExplotionGenerator.h"
#include "AnchoredSpringFG.h"
#include "SpringForceGenerator.h"
#include "ElasticForceGenerator.h"
#include "BuoyancyForceGenerator.h"
#include <set>
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
	std::set<ForceGenerator*> _force_generators;
	std::list <ExplotionGenerator*> _explosion_generator;
	FireworkGenerator* _firework_generator = nullptr; 
	ParticleForceRegistry* _force_registry = nullptr;
	BuoyancyForceGenerator* _bouyancyForce = nullptr;
	GravityForceGenerator* _gravityForce = nullptr;
	void changeK(char key);
	void onParticleDeath(Particle* p);
	void createGenerators();
	void createForceGenerators();
	void registerParticlesToForce(std::list<Particle*> p);
	void registerParticleToForce(Particle* p);
	void explode();
	void addForceWithTime();
	void generateSpringDemo();
	void activeForce(std::string type);
	void generateSlinky();
public:
	void keyPress(unsigned char key);
	void integrate(double t);
	ParticleSystem(const Vector3& g = { 0.0f, -10.0f, 0.0f });
	~ParticleSystem();
	void shootFirework();

};

