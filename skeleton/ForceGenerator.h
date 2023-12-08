#pragma once
#include "Particle.h"
#include <iostream>
#include "core.hpp"

class ForceGenerator {
protected:
	ForceGenerator(){};
public:
	virtual void updateForce(Entity* particle, double t) = 0;
	std::string _name;
	bool active = true;
	double _t = 0.0; // If starting negative --> eternal
	double _duration = -1e10;
	virtual inline void activateForce() = 0;
	inline bool updateTime(double t) {
		_t += t;
		return _t < _duration || _duration < 0.0; // Devuelve true si ya era cero o si es positivo
	}
	virtual ~ForceGenerator() {}
};
