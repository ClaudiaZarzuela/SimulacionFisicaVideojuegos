#pragma once
#include "ParticleGenerator.h"
class GaussianParticleGenerator: public ParticleGenerator
{
public:
	GaussianParticleGenerator(Vector3 std_dev_pos, Vector3 mean_pos, Vector3 std_dev_vel, Vector3 mean_vel, int numP = 1);
	GaussianParticleGenerator(Vector3 std_dev_pos, Vector3 mean_pos, Vector3 std_dev_vel, Vector3 mean_vel, PxScene* gS = nullptr, PxPhysics* gP = nullptr, int numMax = 50);
	virtual std::list<Entity*> generateParticles() override;
	virtual std::list<Entity*>  generateRigidBodies() override;
	~GaussianParticleGenerator();

protected:
	Vector3 _std_dev_pos, _std_dev_vel, _mean_pos, _mean_vel;
	std::normal_distribution<float>* velNormalX;
	std::normal_distribution<float>* velNormalY;
	std::normal_distribution<float>* velNormalZ;
	std::normal_distribution<float>* posNormalX;
	std::normal_distribution<float>* posNormalY;
	std::normal_distribution<float>* posNormalZ;
};

