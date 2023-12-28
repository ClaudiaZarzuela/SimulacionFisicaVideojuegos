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
#include "SolidoRigido.h"
#include "Nest.h"

class LevelSystem
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

	Nest* _nest = nullptr;
	PxScene* gScene = nullptr;
	PxPhysics* gPhysics = nullptr;
	Vector3 _gravity;
	std::list<Entity*> _particles;
	std::list<SolidoRigido*> _objPorNivel;
	Particle* _particleBouyancy;
	std::list <ParticleGenerator*> _particle_generators;
	std::list <ParticleGenerator*> _rigidBody_generator;
	std::set<ForceGenerator*> _force_generators;
	std::list <ExplotionGenerator*> _explosion_generator;
	FireworkGenerator* _firework_generator = nullptr;
	ParticleForceRegistry* _force_registry = nullptr;
	BuoyancyForceGenerator* _bouyancyForce = nullptr;
	GravityForceGenerator* _gravityForce = nullptr;

	void changeK(char key) {};
	void onParticleDeath(Particle* p) {};
	void createGenerators() {};
	void createForceGenerators() {};
	void createSolidoRigidoGenerators() {};
	void registerParticlesToForce(std::list<Entity*> p) {};
	void registerParticleToForce(Entity* p) {};
	void explode() {};
	void addForceWithTime() {};
	void generateSpringDemo() {};
	void generateBouyancy() {};
	void activeForce(std::string type) {};
	void generateSlinky() {};
	void changeMass(char key) {};
	void changeVolume(char key) {};
	void showAvailableKeys() {};
public:
	void keyPress(unsigned char key) {};
	void integrate(double t) {};
	void handleMouse(int button, int state, int x, int y) {};
	LevelSystem(PxScene* gS, PxPhysics* gP, const Vector3& g = { 0.0f, -10.0f, 0.0f }):gScene(gS), gPhysics(gP){};
	~LevelSystem() {};
	void startLevel1();
	void shootFirework() {};
};

