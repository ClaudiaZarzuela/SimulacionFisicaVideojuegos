#include "LevelSystem.h"

LevelSystem::LevelSystem(PxScene* gS, PxPhysics* gP, const Vector3& g) {
	gPhysics = gP;
	gScene = gS;
	_gravity = g;
	
	_firework_generator = new FireworkGenerator();

}
void LevelSystem::addForces() {
	_force_registry = new ParticleForceRegistry();
	_gravityForce = new GravityForceGenerator(_gravity);
	_force_generators.insert(_gravityForce);

}
void LevelSystem::startLevel1() {
	gravity = -10.0f;
	addForces();
	_particle_generators.push_back(new UniformParticleGenerator(Vector3(-150, 70, -120), Vector3(150, 70, -40), Vector3(0.1, 0.1, 0.1), Vector3(0.1, 0.1, 0.1)));

	_player = new Player(gScene, gPhysics, { 0,-12,-100 }, { 7, 7, 7 }, 10000, 10000);

	_nest = new Nest(gScene, gPhysics, { 0,-40,-100});

	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { 0,-45,-80 }, { 150, 0.1, 40 }));
	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { 0,-29,-100 }, { 0,0,0 }, { 0,0,0 }, { 7, 10, 7 }, 10000,10000, { 1,0.5,1,1 },-1,"BOX","NORMAL",false));
}

void LevelSystem::startLevel2() {
	gravity = -10.0f;
	addForces();
	_particle_generators.push_back(new UniformParticleGenerator(Vector3(-150, 70, -120), Vector3(150, 70, -40), Vector3(0.1, -60, 0.1), Vector3(0.1, -50, 0.1),nullptr, nullptr, 0));
	_force_generators.insert(new ParticleDragGenerator(2, 0, { 0,-47,-80 }, { 150, 0.1, 40 }, 120, Vector3(60, -80, 0)));

	_player = new Player(gScene, gPhysics, { 0,18,-100 }, {7,7,7}, 1, 1);
	
	_nest = new Nest(gScene, gPhysics, { 0,-43,-100 });

	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { 0,3,-100 }, { 0,-1,0 }, { 0,0,0 }, { 8,8,8 }, 1, 1, { 0,1,1,1 }, -1, "BOX", "NORMAL", false));
	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { 0,-8,-100 }, { 0,-1,0 }, { 0,0,0 },  { 17,3,17 }, 1,1 , { 0,0.7,0.7,1 }, -1, "BOX", "NORMAL", false));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { 18,-18,-100 }, { 7,7,7 }, 1, 1));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { -18,-18,-100 }, { 7,7,7}, 1, 1));
	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { 0,-28,-100 }, { 17,3,17 }, { 0,0.5,0.5,1 }));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { 0,-45,-80 }, { 150, 0.1, 40 }));
}

void LevelSystem::startLevel3() {
	gravity = -10.0f;
	addForces();
	_particle_generators.push_back(new UniformParticleGenerator(Vector3(-150, 70, -120), Vector3(150, 70, -40), Vector3(0.1, -20, 0.1), Vector3(0.1, -10, 0.1), nullptr, nullptr, 0));
	_force_generators.insert(new ParticleDragGenerator(2, 0, { 0,-47,-80 }, { 150, 0.1, 40 }, 120, Vector3(-40, 0, 0)));

	_player = new Player(gScene, gPhysics, { -40,22,-100 }, { 5,5,5 }, 1, 1);

	_nest = new Nest(gScene, gPhysics, { 40,-40,-100 });

	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { -40,11,-100 }, { 0,-1,0 }, { 0,0,0 }, {6,6,6}, 1, 1, { 0,1,1,1 }, -1, "BOX", "NORMAL", false));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, {-40,-1,-100 }, {6,6,6}, 1, 1));
	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { -40,-8,-100 }, { 0,-1,0 }, { 0,0,0 }, {8,1,8 }, 1, 1, { 0,1,1,1 }, -1, "BOX", "NORMAL", false));
	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { -40,-21,-100 }, { 0,-1,0 }, { 0,0,0 }, { 6,12,6 }, 1, 1, { 0,1,1,1 }, -1, "BOX", "NORMAL", false));
	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { -50,-39,-100 },{ 6,6,6 }, { 0,1,1,1 }));
	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { -30,-39,-100 },{ 6,6,6 },{ 0,1,1,1 }));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { 0,-46,-80 }, { 150, 1, 40 }));

}
void LevelSystem::startLevel4() {
	gravity = -100.0f;
	addForces();
	_player = new Player(gScene, gPhysics, { 4,16,-100 }, { 7,5,7 }, 1, 1);
	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, {-5,6,-100}, {0,-1,0}, {0,0,0}, { 7,5,7 }, 1, 1, {0,1,1,1}, -1, "BOX", "NORMAL", false));
	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { 4,-4,-100 }, { 0,-1,0 }, { 0,0,0 }, { 7,5,7 }, 1, 1, { 0,0.8,0.8,1 }, -1, "BOX", "NORMAL", false));
	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { -5,-14,-100 }, { 0,-1,0 }, { 0,0,0 }, { 7,5,7 }, 1, 1, { 0,0.6,0.6,1 }, -1, "BOX", "NORMAL", false));
	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { 4,-24,-100 }, { 0,-1,0 }, { 0,0,0 }, { 7,5,7 }, 1, 1, { 0,0.4,0.4,1 }, -1, "BOX", "NORMAL", false));
	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { -5,-34,-100 }, { 0,-1,0 }, { 0,0,0 }, { 7,5,7 }, 1, 1, { 0,0.2,0.2,1 }, -1, "BOX", "NORMAL", false));

	_nest = new Nest(gScene, gPhysics, { 0,-40,-100 },20);

	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { 30,11,-100 }, { 10,5,10 }, 1, 1, {1,0.8,0.8,1}));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { 30,1,-100 }, { 10,5,10 }, 1, 1, {1,0.6,0.6,1}));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { 30,-9,-100 }, { 10,5,10 }, 1, 1, {1,0.4,0.4,1}));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { 30,-19,-100 }, { 10,5,10 }, 1, 1, { 1,0.2,0.2,1 }));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { 30,-29,-100 }, { 10,5,10 }, 1, 1, { 1,0,0,1 }));
	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { 30,-39,-100 }, { 10,5,10 }, { 0,0.5,0.5,1 }));

	/*_objPorNivel.push_back(new Enemy(gScene, gPhysics, { -20,-18,-100 }, { 5,5,5 }, 1, 1));
	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { 0,-25,-100 }, {5,5,5 }, { 0,0.5,0.5,1 }));*/

	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { -30,11,-100 }, { 10,5,10 }, 1, 1, { 1,0.8,0.8,1 }));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { -30,1,-100 }, { 10,5,10 }, 1, 1, { 1,0.6,0.6,1 }));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { -30,-9,-100 }, { 10,5,10 }, 1, 1, { 1,0.4,0.4,1 }));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { -30,-19,-100 }, { 10,5,10 }, 1, 1, { 1,0.2,0.2,1 }));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { -30,-29,-100 }, { 10,5,10 }, 1, 1, { 1,0,0,1 }));
	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { -30,-39,-100 }, { 10,5,10 }, { 0,0.5,0.5,1 }));

	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { 0,-45,-80 }, { 150, 1, 40 }));

	//_objPorNivel.push_back(new Enemy(gScene, gPhysics, { -20,-18,-100 }, { 5,5,5 }, 1, 1));
	/*_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { 0,-28,-100 }, { 17,3,17 }, { 0,0.5,0.5,1 }));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { 0,-45,-80 }, { 150, 0.1, 40 }));*/
}
void LevelSystem::startLevel5() {
	addForces();
	_particle_generators.push_back(new UniformParticleGenerator(Vector3(-150, 70, -120), Vector3(150, 70, -40), Vector3(0.1, -60, 0.1), Vector3(0.1, -50, 0.1), nullptr, nullptr, 0));
	_force_generators.insert(new ParticleDragGenerator(2, 0, { 0,-47,-80 }, { 150, 0.1, 40 }, 120, Vector3(60, -80, 0)));

	_player = new Player(gScene, gPhysics, { 0,18,-100 }, { 7,7,7 }, 1, 1);

	_nest = new Nest(gScene, gPhysics, { 0,-40,-100 });

	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { 0,3,-100 }, { 0,0,0 }, { 0,0,0 }, { 8,8,8 }, 1, 1, { 0,1,1,1 }, -1, "BOX", "NORMAL", false));
	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { 0,-8,-100 }, { 0,0,0 }, { 0,0,0 }, { 17,3,17 }, 1, 1, { 0,0.7,0.7,1 }, -1, "BOX", "NORMAL", false));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { 20,-18,-100 }, { 7,7,7 }, 1, 1));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { -20,-18,-100 }, { 7,7,7 }, 1, 1));
	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { 0,-28,-100 }, { 17,3,17 }, { 0,0.5,0.5,1 }));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { 0,-45,-80 }, { 150, 0.1, 40 }));
}
void LevelSystem::startLevel6() {
	addForces();
	_particle_generators.push_back(new UniformParticleGenerator(Vector3(-150, 70, -120), Vector3(150, 70, -40), Vector3(0.1, -60, 0.1), Vector3(0.1, -50, 0.1), nullptr, nullptr, 0));
	_force_generators.insert(new ParticleDragGenerator(2, 0, { 0,-47,-80 }, { 150, 0.1, 40 }, 120, Vector3(60, -80, 0)));

	_player = new Player(gScene, gPhysics, { 0,18,-100 }, { 7,7,7 }, 1, 1);

	_nest = new Nest(gScene, gPhysics, { 0,-40,-100 });

	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { 0,3,-100 }, { 0,0,0 }, { 0,0,0 }, { 8,8,8 }, 1, 1, { 0,1,1,1 }, -1, "BOX", "NORMAL", false));
	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { 0,-8,-100 }, { 0,0,0 }, { 0,0,0 }, { 17,3,17 }, 1, 1, { 0,0.7,0.7,1 }, -1, "BOX", "NORMAL", false));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { 20,-18,-100 }, { 7,7,7 }, 1, 1));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { -20,-18,-100 }, { 7,7,7 }, 1, 1));
	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { 0,-28,-100 }, { 17,3,17 }, { 0,0.5,0.5,1 }));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { 0,-45,-80 }, { 150, 0.1, 40 }));
}
void LevelSystem::startLevel7() {
	addForces();
	_particle_generators.push_back(new UniformParticleGenerator(Vector3(-150, 70, -120), Vector3(150, 70, -40), Vector3(0.1, -60, 0.1), Vector3(0.1, -50, 0.1), nullptr, nullptr, 0));
	_force_generators.insert(new ParticleDragGenerator(2, 0, { 0,-47,-80 }, { 150, 0.1, 40 }, 120, Vector3(60, -80, 0)));

	_player = new Player(gScene, gPhysics, { 0,18,-100 }, { 7,7,7 }, 1, 1);

	_nest = new Nest(gScene, gPhysics, { 0,-40,-100 });

	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { 0,3,-100 }, { 0,0,0 }, { 0,0,0 }, { 8,8,8 }, 1, 1, { 0,1,1,1 }, -1, "BOX", "NORMAL", false));
	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { 0,-8,-100 }, { 0,0,0 }, { 0,0,0 }, { 17,3,17 }, 1, 1, { 0,0.7,0.7,1 }, -1, "BOX", "NORMAL", false));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { 20,-18,-100 }, { 7,7,7 }, 1, 1));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { -20,-18,-100 }, { 7,7,7 }, 1, 1));
	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { 0,-28,-100 }, { 17,3,17 }, { 0,0.5,0.5,1 }));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { 0,-45,-80 }, { 150, 0.1, 40 }));
}
void LevelSystem::startLevel8() {
	addForces();
	_particle_generators.push_back(new UniformParticleGenerator(Vector3(-150, 70, -120), Vector3(150, 70, -40), Vector3(0.1, -60, 0.1), Vector3(0.1, -50, 0.1), nullptr, nullptr, 0));
	_force_generators.insert(new ParticleDragGenerator(2, 0, { 0,-47,-80 }, { 150, 0.1, 40 }, 120, Vector3(60, -80, 0)));

	_player = new Player(gScene, gPhysics, { 0,18,-100 }, { 7,7,7 }, 1, 1);

	_nest = new Nest(gScene, gPhysics, { 0,-40,-100 });

	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { 0,3,-100 }, { 0,0,0 }, { 0,0,0 }, { 8,8,8 }, 1, 1, { 0,1,1,1 }, -1, "BOX", "NORMAL", false));
	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { 0,-8,-100 }, { 0,0,0 }, { 0,0,0 }, { 17,3,17 }, 1, 1, { 0,0.7,0.7,1 }, -1, "BOX", "NORMAL", false));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { 20,-18,-100 }, { 7,7,7 }, 1, 1));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { -20,-18,-100 }, { 7,7,7 }, 1, 1));
	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, { 0,-28,-100 }, { 17,3,17 }, { 0,0.5,0.5,1 }));
	_objPorNivel.push_back(new Enemy(gScene, gPhysics, { 0,-45,-80 }, { 150, 0.1, 40 }));
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

		for (auto it = _particle_generators.begin(); it != _particle_generators.end();) {
			(*it)->updateTime(t);
			auto _newParticles = (*it)->generateParticles();
			registerParticlesToForce(_newParticles);
			_particles.splice(_particles.end(), _newParticles); ++it;
		}

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
			bool die = false;
			auto it = _objPorNivel.begin();
			 while(!die && it != _objPorNivel.end()) {
				 if (((*it)->_type == "ENEMY" || (*it)->_type == "ENEMYFLOOR") && (*it)->insideBoundingBox(_player->getPosition(), _player->_scale, (*it)->getPosition())) {
					_particles.push_back(_firework_generator->shoot(_player->getPosition(), false));
					playerDies(false);
					die = true;
				}
				else ++it;
			}
			if (!die && _nest->insideBoundingBox(_player->getPosition())) {
					_particles.push_back(_firework_generator->shoot(_player->getPosition()));
					playerDies(true);
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

void LevelSystem::explode() {
	auto expl = new ExplotionGenerator(1000000, 1000, 20, {0,-40,-100}, 0.5);
	_force_generators.insert(expl);
	for (auto it = _particles.begin(); it != _particles.end(); ++it)
	{
		_force_registry->addRegistry(expl, *it);
	}
	for (auto it = _objPorNivel.begin(); it != _objPorNivel.end(); ++it)
	{
		_force_registry->addRegistry(expl, *it);
	}
}
void LevelSystem::playerDies(bool _win) {
	explodePlayer = false;
	delete(_player);
	_player = nullptr;
	endGame = true;
	win = _win;
	exp = true;
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
	for (auto it = _objPorNivel.begin(); it != _objPorNivel.end();) {
		delete(*it);
		it = _objPorNivel.erase(it);
	}
	delete(_nest);
	delete(_force_registry);
	_force_registry = nullptr;

	_nest = nullptr;
	actualMenu = 3;
	changeMenu = true;
	explodePlayer = true;
}
void LevelSystem::back() {
	reset();
	if (_player != nullptr)delete(_player);
	_player = nullptr;
}
void LevelSystem::keyPress(unsigned char key) {
	if (active) {
		switch (tolower(key)) {
		case ' ': changeFormPlayer();break;
		default: break;
		}
	}
	
}

void LevelSystem::changeFormEnemy(Entity* obj) {
	bool found = false;
	auto it = _objPorNivel.begin();
	while (!found && it != _objPorNivel.end()) {
		if ((*it) == obj) {
			Entity* aux = obj->changeForm();
			delete(*it);
			it = _objPorNivel.erase(it);
			_objPorNivel.push_back(aux);
			found = true;
		}
		else ++it;
	}
}
	
void LevelSystem::changeFormPlayer() {
	Entity* aux = _player->changeForm();
	delete(_player);
	_player = aux;
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
	for (auto it = _objPorNivel.begin(); it != _objPorNivel.end();) {
		delete(*it);
		it = _objPorNivel.erase(it);
	}

	delete(_firework_generator);
	if(_force_registry != nullptr) delete(_force_registry);
	if (_nest != nullptr)delete(_nest);
	if (_player != nullptr)delete(_player);
}