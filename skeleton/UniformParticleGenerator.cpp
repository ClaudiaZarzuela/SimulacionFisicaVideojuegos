#include "UniformParticleGenerator.h"
#include "Particle.h"
#include "SolidoRigido.h"

#include <iostream>
UniformParticleGenerator::UniformParticleGenerator(Vector3 pos_width_min, Vector3 pos_width_max, Vector3 vel_width_min, Vector3 vel_width_max, PxScene* gS, PxPhysics* gP, int numMax):ParticleGenerator(gS,gP) {
	_pos_width_min = pos_width_min; _pos_width_max = pos_width_max;
	posUniformX = new std::uniform_real_distribution<float>(pos_width_min.x, pos_width_max.x);
	posUniformY = new std::uniform_real_distribution<float>(pos_width_min.y, pos_width_max.y);
	posUniformZ = new std::uniform_real_distribution<float>(pos_width_min.z, pos_width_max.z);

	_vel_width_min = vel_width_min; _vel_width_max = vel_width_max;
	velUniformX = new std::uniform_real_distribution<float>(vel_width_min.x, vel_width_max.x);
	velUniformY = new std::uniform_real_distribution<float>(vel_width_min.y, vel_width_max.y);
	velUniformZ = new std::uniform_real_distribution<float>(vel_width_min.z, vel_width_max.z);
	_n_maxParticles = numMax;
	_n_particles = 1;
}
UniformParticleGenerator::~UniformParticleGenerator() {
	delete(posUniformX);
	delete(posUniformY);
	delete(posUniformZ);

	delete(velUniformX);
	delete(velUniformY);
	delete(velUniformZ);
}

std::list<Entity*> UniformParticleGenerator::generateParticles() {
	std::list<Entity*> particles;
	for (int i = 0; i < _n_particles; ++i) {
		Particle* p = _model_particle->clone();
		p->_pose.p.x = (*posUniformX)(_mt);
		p->_pose.p.y = (*posUniformY)(_mt);
		p->_pose.p.z = (*posUniformZ)(_mt);
		p->_vel.x = (*velUniformX)(_mt);
		p->_vel.y = (*velUniformY)(_mt);
		p->_vel.z = (*velUniformZ)(_mt);
		particles.push_back(p);
	}
	return particles;
}

std::list<Entity*> UniformParticleGenerator::generateRigidBodies() {
	std::list<Entity*> particles;
	SolidoRigido* p = _model_rigidbody->clone();
	Vector3 pos = { (*posUniformX)(_mt),(*posUniformY)(_mt),(*posUniformZ)(_mt) };
	p->setPosition(pos);
	Vector3 vel = { (*velUniformX)(_mt),(*velUniformY)(_mt),(*velUniformZ)(_mt) };
	p->setVelocity(vel);
	time = 0;
	++_n_particles;
	particles.push_back(p);
	return particles;
}