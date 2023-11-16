#include "ParticleGenerator.h"
#include "Particle.h"

ParticleGenerator::ParticleGenerator() {
	_model_particle = new Particle(Vector3(0, 0, 0), Vector3(0, 10, 0), 0.998, 1.0f, 20.0f, Vector4(float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), 1), true);
};

void ParticleGenerator::setParticle(Particle* p) {
	if(_model_particle != nullptr) delete _model_particle;
	_model_particle = p;
}