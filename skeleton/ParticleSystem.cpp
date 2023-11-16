#include "ParticleSystem.h"
ParticleSystem::ParticleSystem(const Vector3& g) {
	_gravity = g;
	createGenerators();
	createForceGenerators();
	inicialiceBoundingBox();
}

void ParticleSystem::createGenerators() {
	//Fuente Gaussiana
	//_particle_generators.push_back(new GaussianParticleGenerator(Vector3(0.01, 0.01, 0.01), Vector3(-50, 0.01, 0.01), Vector3(5, 5, 5), Vector3(2, 25, 2)));
	//Fuente Uniforme
	_particle_generators.push_back(new UniformParticleGenerator(Vector3(0.01, 0.01, 0.01), Vector3(0.01, 0.01, 0.01), Vector3(0.01, 20, -30), Vector3(0.01, 60, -10)));
	//Mangera Uniforme
	//_particle_generators.push_back(new GaussianParticleGenerator(Vector3(1, 0.01, 1), Vector3(50, 5, 0.01),Vector3(1, 0.01, 1), Vector3(0.01, 0.01, 0.01)));
	//Fireworks
	_firework_generator = new FireworkGenerator();
}

void ParticleSystem::createForceGenerators() {
	_force_registry = new ParticleForceRegistry();
	_force_generators.push_back(new ParticleDragGenerator(2, 0, Vector3(0, 0, 0), Vector3(100, 100, 100), Vector3(0,30,-30)));
	//_force_generators.push_back(new ParticleWhirlWindGenerator(Vector3(50, 0, 0), Vector3(20, 100, 20), 1));
	_force_generators.push_back(new GravityForceGenerator(_gravity));
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

void ParticleSystem::inicialiceBoundingBox() {
	//box = { -50, 100, 0, 300, -20, 20 };
	box = { -10000, 10000, 0, 10000, -10000, 10000 };
}

void ParticleSystem::registerParticlesToForce(std::list<Particle*> p) {
	for (auto it = _force_generators.begin(); it != _force_generators.end(); ++it) {
		for (auto ot = p.begin(); ot != p.end(); ++ot) {
			_force_registry->addRegistry(*it, *ot);
		}
	}
}