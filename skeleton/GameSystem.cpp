#include "GameSystem.h"
#include <iostream>
GameSystem::GameSystem(PxScene* gS, PxPhysics* gP, const Vector3& g) {
	gPhysics = gP;
	gScene = gS;
	_gravity = g;

	//Inicilaize GameStateMachine and activate Main Menu Scene
	_gameStateMachine = new GameStateMachine();
	_gameStateMachine->pushState(new MainMenuState("MainMenuState", gScene, gPhysics));

	//Activate proyectil, used as a cursor
	_proyectil = new Weapon(Weapon::Types::LASER);
	showAvailableKeys();
	inicialiceBoundingBox();
}
void GameSystem::showAvailableKeys() {
	std::cout << "CONTROLS:" << std::endl;
	std::cout << "- key 'g' to activate the Gravity Force" << std::endl;
	std::cout << "--------------------------------------------------------" << std::endl;
}

void GameSystem::integrate(double t) {
	_proyectil->integrate(t);
	

	/*for (auto it = _force_generators.begin(); it != _force_generators.end();) {
		if (!(*it)->updateTime(t)) {
			auto aux = (*it);
			_force_registry->deleteForceRegistry(aux);
			it = _force_generators.erase(it); delete (aux);
		}
		else ++it;
	}

	_force_registry->updateForces(t);

	for (auto it = _particles.begin(); it != _particles.end();) {
		if ((*it)->isAlive() && insideBoundingBox((*it)->getPosition())) {
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
	for (auto it = _particle_generators.begin(); it != _particle_generators.end();) {
		auto _newParticles = (*it)->generateParticles();
		registerParticlesToForce(_newParticles);
		_particles.splice(_particles.end(), _newParticles); ++it;
	}
	for (auto it = _rigidBody_generator.begin(); it != _rigidBody_generator.end();) {
		if ((*it)->canGenerateMoreParticles()) {
			(*it)->updateTime(t);
			if ((*it)->hasPassedTimeRequired()) {
				auto _newParticles = (*it)->generateRigidBodies();
				registerParticlesToForce(_newParticles);
				_particles.splice(_particles.end(), _newParticles);
			}
		}
		++it;
	}*/

}
void GameSystem::shootFirework() {
	_particles.push_back(_firework_generator->shoot());
}
bool GameSystem::insideBoundingBox(Vector3 pos) {
	return (pos.x > box.minX && pos.x <= box.maxX) && (pos.y >= box.minY && pos.y <= box.maxY) && (pos.z > box.minZ && pos.z <= box.maxZ);
}
void GameSystem::keyPress(unsigned char key) {
	switch (toupper(key))
	{
		case ' ':
		{
			//_particleSystem->shootFirework(); break;
			std::cout << GetCamera()->getMousePos().x << " " << GetCamera()->getMousePos().y << std::endl;
		}
		case 'T': {
			_proyectil->shoot(GetCamera()->getDir(), GetCamera()->getTransform().p); break;
		}
	default:
		break;
	}
	
}
void GameSystem::handleMouse(int button, int state, int x, int y)
{
	if (button == 0) {
		Vector3 mousePos = { GetCamera()->getMousePos().x,GetCamera()->getMousePos().y, 0 };
		_proyectil->shoot({ mousePos.x/5,mousePos.y/5,-1 }, {0,0,0});
	}
	
}
Vector3 GameSystem::getRayFromScreenSpace(const Vector3& pos)
{
	return { 0,0,0 };
}

void GameSystem::inicialiceBoundingBox() {
	box = { -1000, 1000, -10, 1000, -1000, 1000 };
}

void GameSystem::registerParticlesToForce(std::list<Entity*> p) {
	for (auto it = _force_generators.begin(); it != _force_generators.end(); ++it) {
		for (auto ot = p.begin(); ot != p.end(); ++ot) {
			_force_registry->addRegistry(*it, *ot);
		}
	}
}
void GameSystem::registerParticleToForce(Entity* p) {
	for (auto it = _force_generators.begin(); it != _force_generators.end(); ++it) {
		_force_registry->addRegistry(*it, p);
	}
}
void GameSystem::explode() {
	auto expl = new ExplotionGenerator(100000, 1000, 20, Vector3(0, 10, 0), 0.5);
	_force_generators.insert(expl);
	for (auto it = _particles.begin(); it != _particles.end(); ++it)
	{
		_force_registry->addRegistry(expl, *it);
	}
}
void GameSystem::addForceWithTime() {
	auto aux = new ParticleDragGenerator(2, 0, { -50.0,0.0,0.0 }, Vector3(15, 0.01, 15), 100, Vector3(0, 20, -20), 5);
	_force_generators.insert(aux);
	for (auto it = _particles.begin(); it != _particles.end(); ++it)
	{
		_force_registry->addRegistry(aux, *it);
	}
}

GameSystem::~GameSystem() {

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


	delete(_firework_generator);
	delete(_force_registry);
	delete(_proyectil);
	delete(_gameStateMachine);
}