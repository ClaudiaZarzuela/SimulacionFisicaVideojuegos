#include "ParticleSystem.h"
ParticleSystem::ParticleSystem(const Vector3& g) {
	_gravity = g;
	_particle_generators.push_back(new GaussianParticleGenerator(Vector3(2, 0.01, 2), Vector3(10, 0.01, 5), Vector3(3, 10, 1), Vector3(3, 30, 1), "fuenteG"));

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
			delete(*it);
			it = _particles.erase(it);
		}
	}

	for (auto it = _particle_generators.begin(); it != _particle_generators.end();) {
		_particles.splice(_particles.end(), (*it)->generateParticles()); ++it;
	}
}