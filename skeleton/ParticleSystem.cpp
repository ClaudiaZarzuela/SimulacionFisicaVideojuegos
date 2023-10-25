#include "ParticleSystem.h"
ParticleSystem::ParticleSystem(const Vector3& g) {
	_gravity = g;
	//_particle_generators.push_back(new GaussianParticleGenerator(Vector3(3, 0.01, 0.01), Vector3(-10, 0.01, 0.01), Vector3(5, 5, 5), Vector3(2, 25, 2), "fuenteG",3));
	//_particle_generators.push_back(new UniformParticleGenerator(Vector3(50, 0.01, 0.01), Vector3(50, 0.01, 0.01), Vector3(-2, 30, -2), Vector3(2, 40, 2), "manguera"));
	//_particle_generators.push_back(new UniformParticleGenerator(Vector3(25, 0.01, 0.01), Vector3(30, 0.01, 0.01), Vector3(-2, 20, -2), Vector3(2, 30, 2), "fuenteU"));
	createFireworkSystem();
}
void ParticleSystem::integrate(double t) {
	/*1. Labores de mantenimiento de las partículas
✓ Actualizar el tiempo que lleva “vivo”
✓ Recorrer la lista de partículas y revisar si cada una de ellas ha de seguir viva o no:
❑ Se ha terminado su tiempo de vida
❑ Está fuera de la zona de interés
✓ Eliminar las partículas que “mueren”
✓ Llamar al update de cada partícula
2. Labores de generación de partículas nuevas
✓ Recorrer los distintos generadores
✓ Generar las partículas nuevas
✓ Añadirlas a la lista de partículas
*/

	for (auto it = _particles.begin(); it != _particles.end();) {
		if ((*it)->isAlive()) {
			(*it)->integrate(t); ++it;
		}
		else {
			if ((*it)->type == FIREWORK) onParticleDeath((*it));
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

void ParticleSystem::createFireworkSystem() {
	Vector3 pos = Vector3(0, 0, 0);
    _firework_pool.push_back(new Firework(pos, Vector3(0,30,0), Vector3(0, -10, 0), 0.998, 1.0f, Vector3(0, -10, 0), 3.0f, Vector4(float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), 1), 1, 0, true));
    _firework_pool.push_back(new Firework(pos, Vector3(0,20,0), Vector3(0, -10, 0), 0.998, 1.0f, Vector3(0, -10, 0), 2.0f, Vector4(float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), 1), 3, 1, true, 0.4));
    _firework_pool.push_back(new Firework(pos, Vector3(0,10,0), Vector3(0, -10, 0), 0.998, 1.0f, Vector3(0, -10, 0), 1.0f, Vector4(float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), 1), 4, 2, true, 0.3));
    _firework_pool.push_back(new Firework(pos, Vector3(0,5,0), Vector3(0, -10, 0), 0.998, 1.0f, Vector3(0, -10, 0), 0.5f, Vector4(float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), 1), 5, 3, true, 0.2));
	_firework_generator = new FireworkGenerator(_firework_pool[0], _firework_pool.size());
}

ParticleSystem::~ParticleSystem() {

	for (auto it = _firework_pool.begin(); it != _firework_pool.end();) {
		delete(*it);
		it = _firework_pool.erase(it);
	}

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

void ParticleSystem::onParticleDeath(Particle* p) {
	Firework* f = static_cast<Firework*>(p);
	if(f->getGenerations() < _firework_pool.size()-1) _particles.splice(_particles.end(), f->explode(_firework_pool[f->getGenerations()+1]));
}