#include "GravityForceGenerator.h"
#include <iostream>
void GravityForceGenerator::updateForce(Particle* p, double t) {
	//Check that the particle has Finite Mass
	if (fabs((1 / p->mass)) < 1e-10) return ;
	//Apply the mass scaled gravity
	p->addForce(_gravity * p->mass);
	
}