#include "ParticleWhirlWindGenerator.h"
void ParticleWhirlWindGenerator::updateForce(Particle* particle, double t) {
	if (active) {
		_wind = K * Vector3(-(particle->_pose.p.z - _pos.z) * 7, ((particle->_pose.p.y - _pos.y)), (particle->_pose.p.x - _pos.x));
		ParticleDragGenerator::updateForce(particle, t);
	}
}