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
#include "Button.h"
#include "Player.h"
extern bool changeMenu;
extern int actualMenu;
class LevelSystem
{
public: 
	bool active = false;
	std::list<Entity*> _objPorNivel;

private: 
	struct BoundingBox {
		int minX, maxX;
		int minY, maxY;
		int minZ, maxZ;
	};
	BoundingBox box;
	void inicialiceBoundingBox();
	bool insideBoundingBox(Vector3 pos);
	bool endGame = false;
	int _timer = 3;
	double elapsedTime = 0;

	Nest* _nest = nullptr;
	Entity* _player = nullptr;
	SolidoRigido* suelo = nullptr;
	bool explodePlayer = true;
	PxScene* gScene = nullptr;
	PxPhysics* gPhysics = nullptr;
	Vector3 _gravity;
	std::list<Entity*> _particles;
	Particle* _particleBouyancy;
	std::list <ParticleGenerator*> _particle_generators;
	std::list <ParticleGenerator*> _rigidBody_generator;
	std::set<ForceGenerator*> _force_generators;
	std::list <ExplotionGenerator*> _explosion_generator;
	FireworkGenerator* _firework_generator = nullptr;
	ParticleForceRegistry* _force_registry = nullptr;
	BuoyancyForceGenerator* _bouyancyForce = nullptr;
	GravityForceGenerator* _gravityForce = nullptr;

	void reset();
	void registerParticlesToForce(std::list<Entity*> p);
	void registerParticleToForce(Entity* p);
public:
	void keyPress(unsigned char key);
	void integrate(double t);
	LevelSystem(PxScene* gS, PxPhysics* gP, const Vector3& g = { 0.0f, -10.0f, 0.0f });
	~LevelSystem();
	void startLevel1();
	void startLevel2();
	void shootFirework();
};

