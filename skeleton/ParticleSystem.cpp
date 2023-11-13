#include "ParticleSystem.h"
ParticleSystem::ParticleSystem(const Vector3& g) {
	_gravity = g;
	//createGenerators();
	createForceGenerators();
	inicialiceBoundingBox();
	registerForces();
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

void ParticleSystem::createForceGenerators() {
	_force_registry = new ParticleForceRegistry();
	gravity_generator = new GravityForceGenerator(_gravity);
}

void ParticleSystem::registerForces() {
	for (int i = 0; i < 10; ++i) {
		Particle* aux = new Particle(Vector3(rand() % 10, 0, rand() % 10), Vector3(0, 30, 0), 0.998, 1.0f, 20.0f, Vector4(float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), 1), false);
		_particles.push_back(aux);
		_force_registry->addRegistry(gravity_generator, aux);
	}
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