#pragma once
#include "ParticleDragGenerator.h"
class ParticleWhirlWindGenerator : public ParticleDragGenerator
{
public:
	ParticleWhirlWindGenerator(Vector3 pos, Vector3 Dimensions, int k) :ParticleDragGenerator(pos, Dimensions) {
		K = k; setDrag(2, 0);
	}
	~ParticleWhirlWindGenerator(){}
	void updateForce(Particle* particle, double t);
private:
	int K;
};

