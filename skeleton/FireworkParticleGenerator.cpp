#include "FireworkParticleGenerator.h"
#include "Firework.h"
FireworkParticleGenerator::FireworkParticleGenerator(Firework* f) :GaussianParticleGenerator() {
	_n_particles = f->getNumParticles();
	modelo = f;
	_std_dev_pos = Vector3(f->_pose.p.x + 0.01, f->_pose.p.y + 0.01, f->_pose.p.z + 0.01);
	_mean_pos = Vector3(2, 0.01, 0.01);
	_std_dev_vel = Vector3(f->_vel.x + 0.01, f->_vel.y + 0.01, f->_vel.z + 0.01);
	_mean_vel = Vector3(2, 5, 2);
	calculateNormalDistribution(_std_dev_pos, _mean_pos, _std_dev_vel, _mean_vel);
}

std::list<Particle*> FireworkParticleGenerator::generateParticles() {
	std::list<Particle*> particles;
	for (int i = 0; i < _n_particles; ++i) {
		Firework* p = modelo->clone();
		p->_pose.p.x = (*posNormalX)(_mt);
		p->_pose.p.y = (*posNormalY)(_mt);
		p->_pose.p.z = (*posNormalZ)(_mt);
		p->_vel.x = (*velNormalX)(_mt);
		p->_vel.y = (*velNormalY)(_mt);
		p->_vel.z = (*velNormalZ)(_mt);
		particles.push_back(p);
	}
	return particles;
}