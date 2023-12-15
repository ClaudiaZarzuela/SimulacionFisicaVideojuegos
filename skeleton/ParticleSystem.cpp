#include "ParticleSystem.h"
#include <iostream>
ParticleSystem::ParticleSystem(PxScene* gS, PxPhysics* gP, const Vector3& g) {
	gPhysics = gP;
	gScene = gS;
	_gravity = g;
	showAvailableKeys();
	_force_registry = new ParticleForceRegistry();
	createGenerators();
	createForceGenerators();
	createSolidoRigidoGenerators();
	inicialiceBoundingBox();
}
void ParticleSystem::showAvailableKeys() {
	std::cout << "--------------------------------------------------------" << std::endl;
	std::cout << "LIST OF KEYS:" << std::endl;
	std::cout << "- key 'g' to activate the Gravity Force" << std::endl;
	//std::cout << "- key 'u' to activate the Wind Force" << std::endl;
	std::cout << "- key 'h' to activate the WhirlWind Force" << std::endl;
	std::cout << "- key 'e' to activate the Explosion Force" << std::endl;
	/*std::cout << "- key 'l' to activate the Spring Force" << std::endl;
	std::cout << "- key 'p' to add Wind Force for 5 seconds" << std::endl;
	std::cout << "- key 'i' to increase k value" << std::endl;
	std::cout << "- key 'o' to decrease k value" << std::endl;
	std::cout << "- key 'b' to increase volume to the white cube particle " << std::endl;
	std::cout << "- key 'v' to decrease volume to the white cube particle" << std::endl;
	std::cout << "- key 'm' to increase mass to the white cube particle " << std::endl;
	std::cout << "- key 'n' to decrease mass to the white cube particle" << std::endl;*/
	std::cout << "--------------------------------------------------------" << std::endl;
}
void ParticleSystem::createGenerators() {
	_particle_generators.push_back(new UniformParticleGenerator( Vector3(-5, 5, -1), Vector3(0.01, 5, 1), Vector3(-10, 30, -10), Vector3(10, 30, 10)));
	//_particle_generators.push_back(new GaussianParticleGenerator(Vector3(3, 0.01, 5), Vector3(27, 1 ,0.01), Vector3(2, 5, 2), Vector3(2, 25, 2),1));
	_particle_generators.push_back(new GaussianParticleGenerator(Vector3(1, 0.01, 1), Vector3(100, 5, 0.01), Vector3(0.01, 0.01, 0.01), Vector3(0.01, 0.01, 0.01),1));
	//Fireworks
	_firework_generator = new FireworkGenerator();
}
void ParticleSystem::createSolidoRigidoGenerators() {

	//Generar suelo
	SolidoRigido* suelo = new SolidoRigido(gScene, gPhysics, { -2,0,0 }, { 50, 0.1, 50 }, { 0.8,0.8,0.8,1 });
	
	//_rigidBody_generator.push_back(new UniformParticleGenerator(Vector3(-70,50,-5), Vector3(-30,50,5), Vector3(0.01,-20,0.01), Vector3(0.01,-10,0.01), gScene, gPhysics));
	//_rigidBody_generator.push_back(new GaussianParticleGenerator(Vector3(20,0.01,5), Vector3(50,50,0.01), Vector3(0.01,5,0.01), Vector3(0.01,-15,0.01), gScene, gPhysics));
	
	_rigidBody_generator.push_back(new UniformParticleGenerator( Vector3(-5, 5, -1), Vector3(0.01, 5, 1), Vector3(-2, 20, -2), Vector3(2, 30, 2), gScene, gPhysics));
	_rigidBody_generator.push_back(new GaussianParticleGenerator(Vector3(5, 0.01, 3), Vector3(100, 5, 0.01), Vector3(0.01, 0.01, 0.01), Vector3(0.01, 0.01, 0.01), gScene, gPhysics,100));
}
void ParticleSystem::createForceGenerators() {
#pragma region Practica 3
	_gravityForce = new GravityForceGenerator(_gravity);
	_force_generators.insert(_gravityForce);
	//_force_generators.insert(new ParticleDragGenerator(2, 0, { 25,0.0,0.0 }, Vector3(10, 0.01, 10), 100, Vector3(0, 20, -30)));
	_force_generators.insert(new ParticleWhirlWindGenerator(Vector3(100, -10, 0), Vector3(50, 0.01, 50),500, 2));
#pragma endregion

#pragma region Practica 4
	//_gravityForce = new GravityForceGenerator(_gravity);
	//_force_generators.insert(_gravityForce);
	//generateSpringDemo();
	//generateSlinky();
	//generateBouyancy();
#pragma endregion

#pragma region Solido Rigido
//_force_generators.insert(new ParticleDragGenerator(2, 0, { 25,0.0,0.0 }, Vector3(10, 0.01, 10), 100, Vector3(0, 20, -30)));
//_force_generators.insert(new ParticleWhirlWindGenerator(Vector3(100, -10, 0), Vector3(90, 0.01, 90),500, 1));
#pragma endregion
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
	}

}
void ParticleSystem::shootFirework() {
	_particles.push_back(_firework_generator->shoot());
}
bool ParticleSystem::insideBoundingBox(Vector3 pos) {
	return (pos.x > box.minX && pos.x <= box.maxX) && (pos.y >= box.minY && pos.y <= box.maxY) && (pos.z > box.minZ && pos.z <= box.maxZ);
}
void ParticleSystem::keyPress(unsigned char key) {
	
	switch (tolower(key)) {
	case 'e':
		explode();
		break;
		/*case 'p':
		addForceWithTime();
		break;*/
	case 'g':
		activeForce("GRAVITY");
		break;
	/*case 'u': 
		activeForce("WIND");
		break;*/
	case 'h':
		activeForce("WHIRLWIND");
		break;
	/*case 'x':
		activeForce("EXPLOSION");
		break;*/
	/*case 'l':
		activeForce("SPRING");
		break;
	case 'o':
		changeK(tolower(key));
		break;
	case 'i':
		changeK(tolower(key));
		break;
	case 'm':
		changeMass(key);
		break;
	case 'n':
		changeMass(key);
		break;
	case 'v':
		changeVolume(key);
		break;
	case 'b':
		changeVolume(key);
		break;*/
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
	box = { -1000, 1000, -10, 1000, -1000, 1000 };
}
void ParticleSystem::registerParticlesToForce(std::list<Entity*> p) {
	for (auto it = _force_generators.begin(); it != _force_generators.end(); ++it) {
		for (auto ot = p.begin(); ot != p.end(); ++ot) {
			_force_registry->addRegistry(*it, *ot);
		}
	}
}
void ParticleSystem::registerParticleToForce(Entity* p) {
	for (auto it = _force_generators.begin(); it != _force_generators.end(); ++it) {
			_force_registry->addRegistry(*it, p);
	}
}
void ParticleSystem::explode() {
	auto expl = new ExplotionGenerator(100000, 1000, 20, Vector3(0, 10, 0),0.5);
	_force_generators.insert(expl);
	for (auto it = _particles.begin(); it != _particles.end(); ++it)
	{
		_force_registry->addRegistry(expl, *it);
	}
}
void ParticleSystem::addForceWithTime() {
	auto aux = new ParticleDragGenerator(2, 0, { -50.0,0.0,0.0 }, Vector3(15, 0.01, 15), 100, Vector3(0, 20, -20),5);
	_force_generators.insert(aux);
	for (auto it = _particles.begin(); it != _particles.end(); ++it)
	{
		_force_registry->addRegistry(aux, *it);
	}
}
void ParticleSystem::generateSlinky() {
	Particle* p1 = new Particle({50,70,0 }, { 0.0,0.0,0.0 }, 0.998, 1.0, 60);
	AnchoredSpringFG* f0 = new AnchoredSpringFG(10, 6, {50,75,0});
	_force_generators.insert(f0);
	_force_registry->addRegistry(f0, p1);
	_particles.push_back(p1);

	for (int i = 0; i < 5; ++i) {

		Particle* p2 = new Particle({ 50,(float)(65 - (i * 5)),0}, {0.0,0.0,0.0}, 0.998, 1.0, 60);
		_particles.push_back(p2);

		SpringForceGenerator* f1 = new SpringForceGenerator(10, 6, p2);
		SpringForceGenerator* f2 = new SpringForceGenerator(10, 6, p1);

		_force_generators.insert(f1);
		_force_generators.insert(f2);

		_force_registry->addRegistry(f1, p1);
		_force_registry->addRegistry(f2, p2);
		_force_registry->addRegistry(_gravityForce, p1);
		_force_registry->addRegistry(_gravityForce, p2);

		p1 = p2;

	}
}
void ParticleSystem::generateBouyancy() {
	_bouyancyForce = new BuoyancyForceGenerator(1000, {2,0,0});
	_force_generators.insert(_bouyancyForce);

	Particle* p0 = new Particle({ -10.0,20.0,0.0 }, { 0.0,0.0,0.0 }, 0.86, 400.0, 100, false, { 255,255,0,1 }, { 1,1,1 }, Particle::BOX);//amarillo
	_particles.push_back(p0);
	_force_registry->addRegistry(_gravityForce, p0);
	_force_registry->addRegistry(_bouyancyForce, p0);
	std::cout << "Particula Amarilla:" << std::endl;
	std::cout << "Masa: " << p0->mass <<  std::endl << "Volumen: " << p0->getVolume() << std::endl;

	Particle* p2 = new Particle({ 20.0,20.0,0.0 }, { 0.0,0.0,0.0 }, 0.86, 4000.0, 100, false, { 0,1,0,1 }, { 2,4,2 }, Particle::BOX); //verde
	_particles.push_back(p2);
	_force_registry->addRegistry(_gravityForce, p2);
	_force_registry->addRegistry(_bouyancyForce, p2);
	std::cout << "Particula Verde:" << std::endl;
	std::cout << "Masa: " << p2->mass << std::endl << "Volumen: " << p2->getVolume() << std::endl;

	Particle* p1 = new Particle({0.0,20.0,0.0 }, { 0.0,0.0,0.0 }, 0.86, 2000.0, 100, false, { 1,0,0,1 }, { 2,4,2 }, Particle::BOX); //rojo
	_particles.push_back(p1);
	_force_registry->addRegistry(_gravityForce, p1);
	_force_registry->addRegistry(_bouyancyForce, p1);
	std::cout << "Particula Rojo:" << std::endl;
	std::cout << "Masa: " << p1->mass << std::endl << "Volumen: " << p1->getVolume() << std::endl;

	_particleBouyancy = new Particle({10.0,20.0,0.0 }, { 0.0,0.0,0.0 }, 0.86, 400.0, 100, false, { 1,1,1,1 }, { 2,3,2 }, Particle::BOX);//blanco
	_particles.push_back(_particleBouyancy);
	_force_registry->addRegistry(_gravityForce, _particleBouyancy);
	_force_registry->addRegistry(_bouyancyForce, _particleBouyancy);
	std::cout << "Particula Blanco:" << std::endl;
	std::cout << "Masa: " << _particleBouyancy->mass << std::endl << "Volumen: " << _particleBouyancy->getVolume() << std::endl;
	std::cout << "--------------------------------------------------------" << std::endl;

}
void ParticleSystem::changeMass(char key) {
	_particleBouyancy->changeMass(key);
	std::cout << "--------------------------------------------------------" << std::endl;
	std::cout << "Particula Blanco:" << std::endl;
	std::cout << "Masa: " << _particleBouyancy->mass << std::endl << "Volumen: " << _particleBouyancy->getVolume() << std::endl;
	std::cout << "--------------------------------------------------------" << std::endl;

}
void ParticleSystem::changeVolume(char key) {
	_particleBouyancy->changeVolume(key);
	std::cout << "--------------------------------------------------------" << std::endl;
	std::cout << "Particula Blanco:" << std::endl;
	std::cout << "Masa: " << _particleBouyancy->mass << std::endl << "Volumen: " << _particleBouyancy->getVolume() << std::endl;
	std::cout << "--------------------------------------------------------" << std::endl;

}
void ParticleSystem::generateSpringDemo() {

	//Then one spring with one fixed side
	Particle* p3 = new Particle({ -60.0,20.0,0.0 }, { 0.0,0.0,0.0 }, 0.86, 1.0, 100);
	AnchoredSpringFG* f3 = new AnchoredSpringFG(1, 5, { -50.0, 20.0, 0.0 });
	_force_generators.insert(f3);
	_particles.push_back(p3);
	registerParticleToForce(p3);

	//First one standard spring uniting 2 particles
	Particle* p1 = new Particle({ 70.0,20.0,-10.0 }, { 0.0,0.0,0.0 }, 0.998, 1.0, 100);
	Particle* p2 = new Particle({ 110.0,20.0,-10.0 }, { 0.0,0.0,0.0 }, 0.998, 1.0, 100);

	ElasticForceGenerator* f1 = new ElasticForceGenerator(1, 20, p2);
	_force_registry->addRegistry(f1, p1);

	ElasticForceGenerator* f2 = new ElasticForceGenerator(1, 20, p1);
	_force_registry->addRegistry(f2, p2);
	_force_generators.insert(f1);
	_force_generators.insert(f2);

	_particles.push_back(p1);
	_particles.push_back(p2);

	//First one standard spring uniting 2 particles
	Particle* p4 = new Particle({ 70.0,20.0,10.0 }, { 0.0,0.0,0.0 }, 0.998, 1.0, 100);
	Particle* p5 = new Particle({ 110.0,20.0,10.0 }, { 0.0,0.0,0.0 }, 0.998, 1.0, 100);

	SpringForceGenerator* f4 = new SpringForceGenerator(1, 20, p5);
	_force_registry->addRegistry(f4, p4);

	SpringForceGenerator* f5 = new SpringForceGenerator(1, 20, p4);
	_force_registry->addRegistry(f5, p5);
	_force_generators.insert(f4);
	_force_generators.insert(f5);

	_particles.push_back(p4);
	_particles.push_back(p5);
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
	for (auto it = _rigidBody_generator.begin(); it != _rigidBody_generator.end();) {
		delete(*it);
		it = _rigidBody_generator.erase(it);
	}
	

	delete(_firework_generator);
	delete(_force_registry);
}