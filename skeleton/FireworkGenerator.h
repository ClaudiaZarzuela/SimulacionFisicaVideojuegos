#pragma once
#include "Firework.h"
class FireworkGenerator
{
private:
	std::vector<Firework*> _firework_pool;
public:
	Firework* getModel(int gen) { return _firework_pool[gen];}
	Particle* shoot();
	Particle* shoot(Vector3 pos, bool alive);
	std::list<Entity*> explode(Firework* p);
	FireworkGenerator();
	~FireworkGenerator(){
		for (auto it = _firework_pool.begin(); it != _firework_pool.end();) {
			delete(*it);
			it = _firework_pool.erase(it);
		}
	}
};

