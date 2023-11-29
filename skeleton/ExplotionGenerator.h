#pragma once
#include "ForceGenerator.h"
#include <cmath>
class ExplotionGenerator :public ForceGenerator
{
protected:
	int R, K, _t;
	Vector3 origin;
	bool eliminate = false;
	virtual inline void activateForce() override {}

public:
	ExplotionGenerator(int k, int radius, int t, Vector3 o, double duration = 5) : ForceGenerator(), K(k), R(radius), _t(t), origin(o) {
		_name = "EXPLOSION";
		_duration = duration;

	}
	virtual void updateForce(Particle* particle, double t) override;
};

