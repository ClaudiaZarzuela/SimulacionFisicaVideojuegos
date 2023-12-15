#include "GaussianParticleGenerator.h"
#include "Particle.h"
#include "SolidoRigido.h"

GaussianParticleGenerator::GaussianParticleGenerator(Vector3 std_dev_pos, Vector3 mean_pos, Vector3 std_dev_vel, Vector3 mean_vel, PxScene* gS, PxPhysics* gP,int numMax):ParticleGenerator(gS, gP) {
 	_std_dev_pos = std_dev_pos; _std_dev_vel = std_dev_vel; _mean_pos = mean_pos; _mean_vel = mean_vel;
	posNormalX = new std::normal_distribution<float>(mean_pos.x, std_dev_pos.x);
	posNormalY = new std::normal_distribution<float>(mean_pos.y, std_dev_pos.y);
	posNormalZ = new std::normal_distribution<float>(mean_pos.z, std_dev_pos.z);

	velNormalX = new std::normal_distribution<float>(mean_vel.x, std_dev_vel.x);
	velNormalY = new std::normal_distribution<float>(mean_vel.y, std_dev_vel.y);
	velNormalZ = new std::normal_distribution<float>(mean_vel.z, std_dev_vel.z);
	_n_maxParticles = numMax;
	_n_particles = 1;
}
GaussianParticleGenerator::GaussianParticleGenerator(Vector3 std_dev_pos, Vector3 mean_pos, Vector3 std_dev_vel, Vector3 mean_vel, int numP): ParticleGenerator(nullptr, nullptr)
{
	_std_dev_pos = std_dev_pos; _std_dev_vel = std_dev_vel; _mean_pos = mean_pos; _mean_vel = mean_vel;
	posNormalX = new std::normal_distribution<float>(mean_pos.x, std_dev_pos.x);
	posNormalY = new std::normal_distribution<float>(mean_pos.y, std_dev_pos.y);
	posNormalZ = new std::normal_distribution<float>(mean_pos.z, std_dev_pos.z);
	velNormalX = new std::normal_distribution<float>(mean_vel.x, std_dev_vel.x);
	velNormalY = new std::normal_distribution<float>(mean_vel.y, std_dev_vel.y);
	velNormalZ = new std::normal_distribution<float>(mean_vel.z, std_dev_vel.z);
	setNParticles(numP);
}
GaussianParticleGenerator::~GaussianParticleGenerator() {
	delete(posNormalX);
	delete(posNormalY);
	delete(posNormalZ);

	delete(velNormalX);
	delete(velNormalY);
	delete(velNormalZ);
}

std::list<Entity*>GaussianParticleGenerator::generateParticles() {
	std::list<Entity*> particles;
	for (int i = 0; i < _n_particles; ++i) {
		Particle* p = _model_particle->clone();
		p->mass = (rand() % 5) + 1;
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
std::list<Entity*> GaussianParticleGenerator::generateRigidBodies() {
	std::list<Entity*> particles;
	SolidoRigido* p = _model_rigidbody->clone();
	Vector3 pos = { (*posNormalX)(_mt),(*posNormalY)(_mt),(*posNormalZ)(_mt) };
	p->setPosition(pos);
	Vector3 vel = { (*velNormalX)(_mt),(*velNormalY)(_mt),(*velNormalZ)(_mt) };
	p->setVelocity(vel);
	time = 0;
	++_n_particles;
	particles.push_back(p);
	return particles;
}