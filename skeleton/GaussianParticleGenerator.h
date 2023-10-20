#pragma once
#include "ParticleGenerator.h"
class GaussianParticleGenerator: public ParticleGenerator
{
public:
	GaussianParticleGenerator(Vector3 std_dev_pos, Vector3 mean_pos, Vector3 std_dev_vel, Vector3 mean_vel, std::string name);
	virtual std::list<Particle*> generateParticles();

protected:
	Vector3 _std_dev_pos, _std_dev_vel, _mean_pos, _mean_vel;
	std::normal_distribution<float>* velNormalX;
	std::normal_distribution<float>* velNormalY;
	std::normal_distribution<float>* velNormalZ;
	std::normal_distribution<float>* posNormalX;
	std::normal_distribution<float>* posNormalY;
	std::normal_distribution<float>* posNormalZ;
};

