#include "GravityForceGenerator.h"
#include <iostream>
void GravityForceGenerator::updateForce(Particle* p, double t) {
	//Check that the particle has Finite Mass
	if (fabs(p->_inv_mass) < 1e-10) return;
	//Apply the mass scaled gravity
	//std::cout << (_gravity).x <<  " " << _gravity.y << " " << _gravity.z << std::endl;
	std::cout << p->mass << std::endl;
	//std::cout << (_gravity * p->mass).x <<  " " << (_gravity * p->mass).y << " " << (_gravity * p->mass).z << std::endl;
	p->addForce(_gravity * p->mass);
}