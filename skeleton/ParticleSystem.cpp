#include "ParticleSystem.h"
ParticleSystem::ParticleSystem(const Vector3& g) {
	_gravity = g;
	createGenerators();
	inicialiceBoundingBox();
}

void ParticleSystem::createGenerators() {
	//Fuente Gaussiana
	_particle_generators.push_back(new GaussianParticleGenerator(Vector3(3, 0.01, 0.01), Vector3(-10, 0.01, 0.01), Vector3(5, 5, 5), Vector3(2, 25, 2)));
	//Fuente Uniforme
	_particle_generators.push_back(new UniformParticleGenerator(Vector3(50, 0.01, 0.01), Vector3(50, 0.01, 0.01), Vector3(-2, 30, -2), Vector3(2, 40, 2)));
	//Mangera Uniforme
	_particle_generators.push_back(new UniformParticleGenerator(Vector3(25, 0.01, 0.01), Vector3(30, 0.01, 0.01), Vector3(-2, 20, -2), Vector3(2, 30, 2)));
	//Fireworks
	_firework_generator = new FireworkGenerator();
}

void ParticleSystem::integrate(double t) {

	for (auto it = _particles.begin(); it != _particles.end();) {
		if ((*it)->isAlive() && insideBoundingBox((*it)->_pose.p)) {
			(*it)->integrate(t); ++it;
		}
		else {
			if ((*it)->generatesOnDeath()) {
				_particles.splice(_particles.end(), _firework_generator->explode(static_cast<Firework*>(*it)));
			}
			delete(*it);
			it = _particles.erase(it);
		}
	}

	for (auto it = _particle_generators.begin(); it != _particle_generators.end();) {
		_particles.splice(_particles.end(), (*it)->generateParticles()); ++it;
	}
}

void ParticleSystem::shootFirework() {
	_particles.push_back(_firework_generator->shoot());
}

ParticleSystem::~ParticleSystem() {

	for (auto it = _particles.begin(); it != _particles.end();) {
		delete(*it);
		it = _particles.erase(it);
	}

	for (auto it = _particle_generators.begin(); it != _particle_generators.end();) {
		delete(*it);
		it = _particle_generators.erase(it);
	}

	delete(_firework_generator);
}

bool ParticleSystem::insideBoundingBox(Vector3 pos) {
	return (pos.x > box.minX && pos.x <= box.maxX) && (pos.y >= box.minY && pos.y <= box.maxY) && (pos.z > box.minZ && pos.z <= box.maxZ);
}

void ParticleSystem::inicialiceBoundingBox() {
	box = { -50, 100, 0, 300, -20, 20 };
}