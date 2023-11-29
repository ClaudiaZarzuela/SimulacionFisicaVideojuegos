#pragma once
#include "ForceGenerator.h"

class SpringForceGenerator :public ForceGenerator
{
protected:
	double _k;
	double _resting_length;  //Longitud del muelle en reposo
	Particle* _other;
public:
	void changeK(char key) {
		if(key == 'i') _k += 5;
		else { if (_k - 5 > 0) _k -= 5; }
		std::cout << "Valor de k: " << _k << std::endl;
	}
	SpringForceGenerator(double k, double resting_length, Particle* other);
	virtual void updateForce(Particle* particle, double t);
	inline void setK(double k) { _k = k; }
	virtual ~SpringForceGenerator(){};
	virtual inline void activateForce() override {
		active = !active;
		if (active) {
			std::cout << "SPRING FORCE: ACTIVATED" << std::endl;
		}
		else {
			std::cout << "SPRING FORCE: DEACTIVATED" << std::endl;
		}
	}
	
	
};
	

