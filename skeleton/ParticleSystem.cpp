#include "ParticleSystem.h"
#include <iostream>
ParticleSystem::ParticleSystem(const Vector3& g) {
	_gravity = g;
	createGenerators();
	createForceGenerators();
	inicialiceBoundingBox();
}

void ParticleSystem::createGenerators() {
	_particle_generators.push_back(new UniformParticleGenerator( Vector3(-1, 5, -1), Vector3(1, 5, 1), Vector3(-10, 30, -10), Vector3(10, 30, 10)));
	_particle_generators.push_back(new GaussianParticleGenerator(Vector3(3, 0.01, 5), Vector3(27, 1 ,0.01), Vector3(2, 5, 2), Vector3(2, 25, 2)));
	_particle_generators.push_back(new GaussianParticleGenerator(Vector3(1, 0.01, 1), Vector3(100, 5, 0.01), Vector3(0.01, 0.01, 0.01), Vector3(0.01, 0.01, 0.01)));
	//Fireworks
	_firework_generator = new FireworkGenerator();
}

void ParticleSystem::createForceGenerators() {
	_force_registry = new ParticleForceRegistry();
	_force_generators.insert(new GravityForceGenerator(_gravity));
	_force_generators.insert(new ParticleDragGenerator(2, 0, Vector3(25, 0, 0), Vector3(20, 0.01, 20), 100, Vector3(0, 20, -30)));
	_force_generators.insert(new ParticleWhirlWindGenerator(Vector3(100, -10, 0), Vector3(20, 0.01, 20),500, 1));
}

void ParticleSystem::integrate(double t) {
	for (auto it = _particles.begin(); it != _particles.end();) {
		if ((*it)->isAlive() && insideBoundingBox((*it)->_pose.p)) {
			(*it)->integrate(t); ++it;
		}
		else {
			_force_registry->deleteParticleRegistry((*it));
			if ((*it)->generatesOnDeath()) {
				_particles.splice(_particles.end(), _firework_generator->explode(static_cast<Firework*>(*it)));
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
	_force_registry->updateForces(t);
}

void ParticleSystem::shootFirework() {
	_particles.push_back(_firework_generator->shoot());
}

ParticleSystem::~ParticleSystem() {

	for (auto it = _particles.begin(); it != _particles.end();) {
		delete(*it);
		it = _particles.erase(it);
	}
	for (auto it = _force_generators.begin(); it != _force_generators.end();) {
		delete(*it);
		it = _force_generators.erase(it);
	}
	for (auto it = _particle_generators.begin(); it != _particle_generators.end();) {
		delete(*it);
		it = _particle_generators.erase(it);
	}

	delete(_firework_generator);
	delete(_force_registry);
}

bool ParticleSystem::insideBoundingBox(Vector3 pos) {
	return (pos.x > box.minX && pos.x <= box.maxX) && (pos.y >= box.minY && pos.y <= box.maxY) && (pos.z > box.minZ && pos.z <= box.maxZ);
}


void ParticleSystem::keyPress(unsigned char key) {
	
	switch (tolower(key)) {
	case 'e':
		_force_registry->addRegistryToParticles(new ExplotionGenerator(10000, 1000, 20, Vector3(0, 10, 0)), _particles);
		break;
	default: break;
	}
}

void ParticleSystem::inicialiceBoundingBox() {
	box = { -50, 200, 0, 200, -200, 100 };
}

void ParticleSystem::registerParticlesToForce(std::list<Particle*> p) {
	for (auto it = _force_generators.begin(); it != _force_generators.end(); ++it) {
		for (auto ot = p.begin(); ot != p.end(); ++ot) {
			_force_registry->addRegistry(*it, *ot);
		}
	}
}