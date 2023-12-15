#include "ParticleWhirlWindGenerator.h"
void ParticleWhirlWindGenerator::updateForce(Entity* particle, double t) {
	if (active) {
		Vector3 pos = particle->getPosition();
		_wind = K * Vector3(-(pos.z - _pos.z) * 7, ((pos.y - _pos.y)), (pos.x - _pos.x));
		ParticleDragGenerator::updateForce(particle, t);
	}
}