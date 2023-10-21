#pragma once
#include "ParticleGenerator.h"
class UniformParticleGenerator :public ParticleGenerator
{
public: 
	UniformParticleGenerator(Vector3 pos_width_min, Vector3 pos_width_max, Vector3 vel_width_min, Vector3 vel_width_max, std::string name);
	virtual std::list<Particle*> generateParticles() override;

protected:
	Vector3 _pos_width_min, _pos_width_max, _vel_width_min, _vel_width_max;
	std::uniform_real_distribution<float>* velUniformX;
	std::uniform_real_distribution<float>* velUniformY;
	std::uniform_real_distribution<float>* velUniformZ;
	std::uniform_real_distribution<float>* posUniformX;
	std::uniform_real_distribution<float>* posUniformY;
	std::uniform_real_distribution<float>* posUniformZ;
};

