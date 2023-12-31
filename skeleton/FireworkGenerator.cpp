#include "FireworkGenerator.h"
#include "Firework.h"
FireworkGenerator::FireworkGenerator() {
    Vector3 pos = Vector3(0, 0, -100);
    _firework_pool.push_back(new Firework(pos, Vector3(0, 0, 0), Vector3(0, -10, 0), 0.998, 1.0f, Vector3(0, -10, 0), 0.1f, { 0.5,1,0.5,1 }, 1, 0, this, true, {1.25,1.25,1.25}));
    _firework_pool.push_back(new Firework(pos, Vector3(0.01, 2, 0.01), Vector3(0, -10, 0), 0.998, 1.0f, Vector3(0, -10, 0), 0.2f, { 0.5,1,0.5,1 }, 10, 1, this, true, { 1,1,1 }));
    _firework_pool.push_back(new Firework(pos, Vector3(0.01, 1, 0.01), Vector3(0, -10, 0), 0.998, 1.0f, Vector3(0, -10, 0), 0.4f, { 0.6,1,0.6,1 }, 7, 2, this, true, { 0.5,0.5,0.5 }));
    _firework_pool.push_back(new Firework(pos, Vector3(0.01, 0.01, 0.01), Vector3(0, -10, 0), 0.998, 1.0f, Vector3(0, -10, 0), 0.6f, { 0.7,1,0.7,1 }, 5, 3, this, true, { 0.25,0.25,0.25 }));
}

Particle* FireworkGenerator::shoot() {
	return _firework_pool[0]->clone();
}
Particle* FireworkGenerator::shoot(Vector3 pos, bool alive) {
    for (int i = 0; i < _firework_pool.size(); ++i) {
        if (!alive) _firework_pool[i]->_color = { 1,(0.2f*i),+(0.2f * i),1};
        else _firework_pool[i]->_color = { 0.5f +(i*0.1f),1, 0.5f + (i * 0.1f),1};
        _firework_pool[i]->setPosition(pos);
    }
	return _firework_pool[0]->clone();
}

std::list<Entity*> FireworkGenerator::explode(Firework* p) {
    std::list<Entity*> s;
    if(p->getGenerations() < _firework_pool.size()-1) s = p->explode();
    return s;
}
