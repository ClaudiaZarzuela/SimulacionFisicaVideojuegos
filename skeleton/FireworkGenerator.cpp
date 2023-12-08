#include "FireworkGenerator.h"
#include "Firework.h"
FireworkGenerator::FireworkGenerator() {
    Vector3 pos = Vector3(80, 0, 0);
    _firework_pool.push_back(new Firework(pos, Vector3(0, 50, 0), Vector3(0, -10, 0), 0.998, 1.0f, Vector3(0, -10, 0), 1.0f, Vector4(float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), 1), 1, 0, this, true, { 1.25,1.25,1.25 }));
    _firework_pool.push_back(new Firework(pos, Vector3(0.01, 2, 0.01), Vector3(0, -10, 0), 0.998, 1.0f, Vector3(0, -10, 0), 0.4f, Vector4(float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), 1), 10, 1, this, true, { 1,1,1 }));
    _firework_pool.push_back(new Firework(pos, Vector3(0.01, 1, 0.01), Vector3(0, -10, 0), 0.998, 1.0f, Vector3(0, -10, 0), 0.6f, Vector4(float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), 1), 7, 2, this, true, { 0.5,0.5,0.5 }));
    _firework_pool.push_back(new Firework(pos, Vector3(0.01, 0.01, 0.01), Vector3(0, -10, 0), 0.998, 1.0f, Vector3(0, -10, 0), 0.8f, Vector4(float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), 1), 5, 3, this, true, { 0.25,0.25,0.25 }));
}

Particle* FireworkGenerator::shoot() {
	return _firework_pool[0]->clone();
}

std::list<Entity*> FireworkGenerator::explode(Firework* p) {
    std::list<Entity*> s;
    if(p->getGenerations() < _firework_pool.size()-1) s = p->explode();
    return s;
}
