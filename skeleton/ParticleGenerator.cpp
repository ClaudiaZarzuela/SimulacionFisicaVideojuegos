#include "ParticleGenerator.h"
ParticleGenerator::ParticleGenerator() {
	_model_particle = new Particle(Vector3(0, 0, 0), Vector3(0, 50, 0), Vector3(0, -10, 0), 0.998, 1.0f, Vector3(0, -10, 0), 2.0f);
}