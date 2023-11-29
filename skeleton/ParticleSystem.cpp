#include "ParticleSystem.h"
#include <iostream>
ParticleSystem::ParticleSystem(const Vector3& g) {
	_gravity = g;
	//createGenerators();
	createForceGenerators();
	inicialiceBoundingBox();

	std::cout << "LIST OF KEYS TO ACTIVATE FORCES:" << std::endl;
	std::cout << "- key 'g' to activate the Gravity Force" << std::endl;
	std::cout << "- key 'u' to activate the Wind Force" << std::endl;
	std::cout << "- key 'h' to activate the WhirlWind Force" << std::endl;
	std::cout << "- key 'x' to activate the Explosion Force" << std::endl;
	std::cout << "- key 'l' to activate the Spring Force" << std::endl;
	std::cout << "- key 'p' to add Wind Force for 5 seconds" << std::endl;
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
	_gravityForce = new GravityForceGenerator(_gravity);
	_force_generators.insert(_gravityForce);
	//_force_generators.insert(new ParticleDragGenerator(2, 0, { 25,0.0,0.0 }, Vector3(10, 0.01, 10), 100, Vector3(0, 20, -30)));
	//_force_generators.insert(new ParticleWhirlWindGenerator(Vector3(100, -10, 0), Vector3(20, 0.01, 20),500, 1));
	//generateSpringDemo();
	//generateSlinky();

	Particle* p0 = new Particle({ 0.0,20.0,0.0 }, { 0.0,0.0,0.0 }, 0.86, 1.0, 60);
	_bouyancyForce = new BuoyancyForceGenerator(100, 125, 1000);
	_force_generators.insert(_bouyancyForce);
	_particles.push_back(p0);
	_force_registry->addRegistry(_gravityForce, p0);
	_force_registry->addRegistry(_bouyancyForce, p0);
}

void ParticleSystem::integrate(double t) {
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
		if ((*it)->isAlive() && insideBoundingBox((*it)->_pose.p)) {
			(*it)->integrate(t); ++it;
		}
		else {
			_force_registry->deleteParticleRegistry(*it);
			if ((*it)->generatesOnDeath()) {
				auto aux = _firework_generator->explode(static_cast<Firework*>(*it));
				_particles.splice(_particles.end(),aux);
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

}

void ParticleSystem::shootFirework() {
	_particles.push_back(_firework_generator->shoot());
}

ParticleSystem::~ParticleSystem() {

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

	delete(_firework_generator);
	delete(_force_registry);
}

bool ParticleSystem::insideBoundingBox(Vector3 pos) {
	return (pos.x > box.minX && pos.x <= box.maxX) && (pos.y >= box.minY && pos.y <= box.maxY) && (pos.z > box.minZ && pos.z <= box.maxZ);
}


void ParticleSystem::keyPress(unsigned char key) {
	
	switch (tolower(key)) {
	case 'e':
		explode();
		break;
	case 'p':
		addForceWithTime();
		break;
	case 'g':
		activeForce("GRAVITY");
		break;
	case 'u': 
		activeForce("WIND");
		break;
	case 'h':
		activeForce("WHIRLWIND");
		break;
	case 'x':
		activeForce("EXPLOSION");
		break;
	case 'l':
		activeForce("SPRING");
		break;
	case 'o':
		changeK(tolower(key));
		break;
	case 'i':
		changeK(tolower(key));
		break;
	default: break;
	}
}
void ParticleSystem::changeK(char key) {
	for (auto it = _force_generators.begin(); it != _force_generators.end();++it) {
		if ((*it)->_name == "SPRING") static_cast<SpringForceGenerator*>(*it)->changeK(key);

	}
}
void ParticleSystem::activeForce(std::string type) {
	for (auto it = _force_generators.begin(); it != _force_generators.end(); ++it) {
		if ((*it)->_name == type) (*it)->activateForce();
	}
}
void ParticleSystem::inicialiceBoundingBox() {
	box = { -50, 200, -1000, 200, -200, 100 };
}

void ParticleSystem::registerParticlesToForce(std::list<Particle*> p) {
	for (auto it = _force_generators.begin(); it != _force_generators.end(); ++it) {
		for (auto ot = p.begin(); ot != p.end(); ++ot) {
			_force_registry->addRegistry(*it, *ot);
		}
	}
}

void ParticleSystem::registerParticleToForce(Particle* p) {
	for (auto it = _force_generators.begin(); it != _force_generators.end(); ++it) {
			_force_registry->addRegistry(*it, p);
	}
}

void ParticleSystem::explode() {
	auto expl = new ExplotionGenerator(10000, 1000, 20, Vector3(0, 10, 0));
	_force_generators.insert(expl);
	for (auto it = _particles.begin(); it != _particles.end(); ++it)
	{
		_force_registry->addRegistry(expl, *it);
	}
}
void ParticleSystem::addForceWithTime() {
	auto aux = new ParticleDragGenerator(2, 0, { 5.0,-30.0,0.0 }, Vector3(20, 0.01, 20), 100, Vector3(0, 20, -10),5);
	_force_generators.insert(aux);
	for (auto it = _particles.begin(); it != _particles.end(); ++it)
	{
		_force_registry->addRegistry(aux, *it);
	}
}

void ParticleSystem::generateSlinky() {
	Particle* p1 = new Particle({ 0.0,120.0,0.0 }, { 0.0,0.0,0.0 }, 0.998, 1.0, 60);
	Particle* p2 = new Particle({ 0.0,110.0,0.0 }, { 0.0,0.0,0.0 }, 0.998, 1.0, 60);
	Particle* p3 = new Particle({ 0.0,100.0,0.0 }, { 0.0,0.0,0.0 }, 0.998, 1.0, 60);
	Particle* p4 = new Particle({ 0.0,90.0,0.0 }, { 0.0,0.0,0.0 }, 0.998, 1.0, 60);
	Particle* p5 = new Particle({ 0.0,80.0,0.0 }, { 0.0,0.0,0.0 }, 0.998, 1.0, 60);
	Particle* p6 = new Particle({ 0.0,70.0,0.0 }, { 0.0,0.0,0.0 }, 0.998, 1.0, 60);

	_particles.push_back(p1); _particles.push_back(p2); _particles.push_back(p3);
	_particles.push_back(p4); _particles.push_back(p5); _particles.push_back(p6);

	AnchoredSpringFG* f0 = new AnchoredSpringFG(1, 50, { 0.0, 130.0, 0.0 });
	_force_registry->addRegistry(f0, p1);
	_force_generators.insert(f0);

	ElasticForceGenerator* f1 = new ElasticForceGenerator(1, 50, p2);
	_force_registry->addRegistry(f1, p1);
	_force_registry->addRegistry(_gravityForce, p1);
	_force_generators.insert(f1);

	ElasticForceGenerator* f2 = new ElasticForceGenerator(1, 50, p3);
	_force_registry->addRegistry(f2, p2);
	_force_registry->addRegistry(_gravityForce, p2);
	_force_generators.insert(f2);

	ElasticForceGenerator* f3 = new ElasticForceGenerator(1, 50, p4);
	_force_registry->addRegistry(f3, p3);
	_force_registry->addRegistry(_gravityForce, p3);
	_force_generators.insert(f3);

	ElasticForceGenerator* f4 = new ElasticForceGenerator(1, 50, p5);
	_force_registry->addRegistry(f4, p4);
	_force_registry->addRegistry(_gravityForce, p4);
	_force_generators.insert(f4);

	ElasticForceGenerator* f5 = new ElasticForceGenerator(1, 50, p6);
	_force_registry->addRegistry(f5, p5);
	_force_registry->addRegistry(_gravityForce, p5);
	_force_generators.insert(f5);

	_force_registry->addRegistry(_gravityForce, p6);

}

void ParticleSystem::generateSpringDemo() {

	//Then one spring with one fixed side
	Particle* p3 = new Particle({ -10.0,20.0,0.0 }, { 0.0,0.0,0.0 }, 0.86, 1.0, 60);
	AnchoredSpringFG* f3 = new AnchoredSpringFG(1, 10, { 10.0, 20.0, 0.0 });
	_force_generators.insert(f3);
	_particles.push_back(p3);
	registerParticleToForce(p3);

	//First one standard spring uniting 2 particles
	Particle* p1 = new Particle({ 50.0,20.0,0.0 }, { 0.0,0.0,0.0 }, 0.998, 1.0, 60);
	Particle* p2 = new Particle({ 90.0,20.0,0.0 }, { 0.0,0.0,0.0 }, 0.998, 1.0, 60);

	SpringForceGenerator* f1 = new SpringForceGenerator(1, 20, p2);
	_force_registry->addRegistry(f1, p1);

	SpringForceGenerator* f2 = new SpringForceGenerator(1, 20, p1);
	_force_registry->addRegistry(f2, p2);
	_force_generators.insert(f1);
	_force_generators.insert(f2);

	_particles.push_back(p1);
	_particles.push_back(p2);
}