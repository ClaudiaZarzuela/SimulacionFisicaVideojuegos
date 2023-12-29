#include "LevelSystem.h"

LevelSystem::LevelSystem(PxScene* gS, PxPhysics* gP, const Vector3& g) {
	gPhysics = gP;
	gScene = gS;
	_gravity = g;
	
	_firework_generator = new FireworkGenerator();

}
void LevelSystem::startLevel1() {
	_force_registry = new ParticleForceRegistry();
	_gravityForce = new GravityForceGenerator(_gravity);
	_force_generators.insert(_gravityForce);

	suelo = new SolidoRigido(gScene, gPhysics, { 0,-45,-80 }, { 150, 0.1, 40 }, { 1,1,1,1 });

	_player = new Player(gScene, gPhysics, { 0,8,-100 }, { 7, 7, 7 }, 10000, 10000);
	registerParticleToForce(_player);

	_nest = new Nest(gScene, gPhysics, { 0,-40,-100});

	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { 0,-19,-100 }, { 0,0,0 }, { 0,0,0 }, { 7, 20, 7 }, 10000,10000, { 1,0.5,1,1 },-1,false));
	registerParticlesToForce(_objPorNivel);
}
void LevelSystem::startLevel2() {
	_force_registry = new ParticleForceRegistry();
	_gravityForce = new GravityForceGenerator(_gravity);
	_force_generators.insert(_gravityForce);

	_nest = new Nest(gScene, gPhysics, { 0,0,-100 });
	_player = new Player(gScene, gPhysics, { 0,8,-100 }, { 7, 7, 7 }, 10000, 10000);
	suelo = new SolidoRigido(gScene, gPhysics, { 0,-45,-80 }, { 150, 0.1, 40 }, { 1,1,1,1 });

}
void LevelSystem::registerParticleToForce(Entity* p) {
	for (auto it = _force_generators.begin(); it != _force_generators.end(); ++it) {
		_force_registry->addRegistry(*it, p);
	}
}
void LevelSystem::registerParticlesToForce(std::list<Entity*> p) {
	for (auto it = _force_generators.begin(); it != _force_generators.end(); ++it) {
		for (auto ot = p.begin(); ot != p.end(); ++ot) {
			_force_registry->addRegistry(*it, *ot);
		}
	}
}
void LevelSystem::shootFirework() {
	_particles.push_back(_firework_generator->shoot());
}
void LevelSystem::integrate(double t) {
	if (active) {
		for (auto it = _force_generators.begin(); it != _force_generators.end();) {
			if (!(*it)->updateTime(t)) {
				auto aux = (*it);
				_force_registry->deleteForceRegistry(aux);
				it = _force_generators.erase(it); delete (aux);
			}
			else ++it;
		}

		_force_registry->updateForces(t);

		for (auto it = _particles.begin(); it != _particles.end();) {
			if ((*it)->isAlive()) {
				(*it)->integrate(t); ++it;
			}
			else {
				_force_registry->deleteParticleRegistry(*it);
				if ((*it)->generatesOnDeath()) {
					auto aux = _firework_generator->explode(static_cast<Firework*>(*it));
					_particles.splice(_particles.end(), aux);
					registerParticlesToForce(aux);
				}
				delete(*it);
				it = _particles.erase(it);
			}
		}
		if (explodePlayer) {
			if (_nest->insideBoundingBox(_player->getPosition())) {
					_particles.push_back(_firework_generator->shoot(_player->getPosition(), true));
					explodePlayer = false;
					delete(_player);
					_player = nullptr;
					endGame = true;
					
			}
		}

	}
	if (endGame) {
		elapsedTime += t;
		if (elapsedTime >= _timer) {
			active = false;
			reset();
			endGame = false;
			elapsedTime = 0;
		}
	}

}

void LevelSystem::reset() {
	for (auto it = _particles.begin(); it != _particles.end();) {
		delete(*it);
		it = _particles.erase(it);
	}
	for (auto it = _explosion_generator.begin(); it != _explosion_generator.end();) {
		delete(*it);
		it = _explosion_generator.erase(it);
	}
	for (auto it = _force_generators.begin(); it != _force_generators.end();) {
		delete(*it);
		it = _force_generators.erase(it);
	}
	for (auto it = _particle_generators.begin(); it != _particle_generators.end();) {
		delete(*it);
		it = _particle_generators.erase(it);
	}
	for (auto it = _rigidBody_generator.begin(); it != _rigidBody_generator.end();) {
		delete(*it);
		it = _rigidBody_generator.erase(it);
	}
	for (auto it = _objPorNivel.begin(); it != _objPorNivel.end();) {
		delete(*it);
		it = _objPorNivel.erase(it);
	}
	delete(_nest);
	delete(_force_registry);
	delete(suelo);

	_nest = nullptr;
	suelo = nullptr;
	_force_registry = nullptr;
	actualMenu = 1;
	changeMenu = true;
	explodePlayer = true;
}
void LevelSystem::keyPress(unsigned char key) {
	if (active) {
		switch (tolower(key)) {
			default: break;
		}
	}
	
}
void LevelSystem::inicialiceBoundingBox() {
	box = { -1000, 1000, -1000, 1000, -1000, 1000 };
}
bool LevelSystem::insideBoundingBox(Vector3 pos) {
	return (pos.x > box.minX && pos.x <= box.maxX) && (pos.y >= box.minY && pos.y <= box.maxY) && (pos.z > box.minZ && pos.z <= box.maxZ);
}
LevelSystem::~LevelSystem() {
	for (auto it = _particles.begin(); it != _particles.end();) {
		delete(*it);
		it = _particles.erase(it);
	}
	for (auto it = _explosion_generator.begin(); it != _explosion_generator.end();) {
		delete(*it);
		it = _explosion_generator.erase(it);
	}
	for (auto it = _force_generators.begin(); it != _force_generators.end();) {
		delete(*it);
		it = _force_generators.erase(it);
	}
	for (auto it = _particle_generators.begin(); it != _particle_generators.end();) {
		delete(*it);
		it = _particle_generators.erase(it);
	}
	for (auto it = _rigidBody_generator.begin(); it != _rigidBody_generator.end();) {
		delete(*it);
		it = _rigidBody_generator.erase(it);
	}
	for (auto it = _objPorNivel.begin(); it != _objPorNivel.end();) {
		delete(*it);
		it = _objPorNivel.erase(it);
	}

	delete(_firework_generator);
	if(_force_registry != nullptr) delete(_force_registry);
	if (_nest != nullptr)delete(_nest);
	if (_player != nullptr)delete(_player);
	if (suelo != nullptr)delete(suelo);
}