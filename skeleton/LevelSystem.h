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
#include "Enemy.h"
extern bool changeMenu;
extern int actualMenu;
extern bool win;
extern float gravity;
class LevelSystem
{
public: 
	bool active = false;
	std::list<Entity*> _objPorNivel;
	bool endGame = false;

private: 
	struct BoundingBox {
		int minX, maxX;
		int minY, maxY;
		int minZ, maxZ;
	};
	BoundingBox box;
	void inicialiceBoundingBox();
	bool insideBoundingBox(Vector3 pos);
	int _timer = 3;
	double elapsedTime = 0;
	bool exp = true;
	Nest* _nest = nullptr;
	Entity* _player = nullptr;
	bool explodePlayer = true;
	PxScene* gScene = nullptr;
	PxPhysics* gPhysics = nullptr;
	Vector3 _gravity;
	std::list<Entity*> _particles;
	std::list <ParticleGenerator*> _particle_generators;
	std::set<ForceGenerator*> _force_generators;
	std::list <ExplotionGenerator*> _explosion_generator;
	FireworkGenerator* _firework_generator = nullptr;
	ParticleForceRegistry* _force_registry = nullptr;
	GravityForceGenerator* _gravityForce = nullptr;

	void registerParticlesToForce(std::list<Entity*> p);
	void registerParticleToForce(Entity* p);
	void playerDies(bool _win);
	void addForces();
	void explode();
	void reset();
public:
	void back();
	void changeFormEnemy(Entity* obj);
	void changeFormPlayer();
	void keyPress(unsigned char key);
	void integrate(double t);
	LevelSystem(PxScene* gS, PxPhysics* gP, const Vector3& g = { 0.0f, -10.0f, 0.0f });
	~LevelSystem();
	void startLevel1();
	void startLevel2();
	void startLevel3();
	void startLevel4();
	void startLevel5();
	void startLevel6();
	void startLevel7();
	void startLevel8();
	void shootFirework();
};

