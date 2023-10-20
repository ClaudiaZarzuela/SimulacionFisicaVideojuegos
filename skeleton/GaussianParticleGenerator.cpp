#include "GaussianParticleGenerator.h"
GaussianParticleGenerator::GaussianParticleGenerator(Vector3 std_dev_pos, Vector3 std_dev_vel):ParticleGenerator() {
	Particle* p = _model_particle->clone();

}