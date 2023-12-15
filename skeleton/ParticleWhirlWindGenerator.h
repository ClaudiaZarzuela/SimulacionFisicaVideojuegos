#pragma once
#include "ParticleDragGenerator.h"
class ParticleWhirlWindGenerator : public ParticleDragGenerator
{
public:
	ParticleWhirlWindGenerator(Vector3 pos, Vector3 Dimensions,int h, int k) :ParticleDragGenerator(pos, Dimensions, h) {
		_name = "WHIRLWIND"; K = k; setDrag(2,0);
	}
	~ParticleWhirlWindGenerator(){}
	virtual void updateForce(Entity* particle, double t);
	virtual inline void activateForce() override {
		active = !active;
		if (active) {
			std::cout << "WHIRLWIND FORCE: ACTIVATED" << std::endl;
		}
		else {
			std::cout << "WHIRLWIND FORCE: DEACTIVATED" << std::endl;
		}
	}
private:
	int K;
};

