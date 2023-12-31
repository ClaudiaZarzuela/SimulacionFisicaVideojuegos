#pragma once
#include "ParticleGenerator.h"
class UniformParticleGenerator :public ParticleGenerator
{
public: 
	UniformParticleGenerator(Vector3 pos_width_min, Vector3 pos_width_max, Vector3 vel_width_min, Vector3 vel_width_max, PxScene* gS = nullptr, PxPhysics* gP = nullptr, float t = 0.1,int numMax = 50);
	virtual std::list<Entity*> generateParticles() override;
	virtual std::list<Entity*>  generateRigidBodies() override;
	~UniformParticleGenerator();

protected:
	Vector3 _pos_width_min, _pos_width_max, _vel_width_min, _vel_width_max;
	std::uniform_real_distribution<float>* velUniformX;
	std::uniform_real_distribution<float>* velUniformY;
	std::uniform_real_distribution<float>* velUniformZ;
	std::uniform_real_distribution<float>* posUniformX;
	std::uniform_real_distribution<float>* posUniformY;
	std::uniform_real_distribution<float>* posUniformZ;
};

