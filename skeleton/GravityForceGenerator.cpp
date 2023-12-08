#include "GravityForceGenerator.h"
#include <iostream>
void GravityForceGenerator::updateForce(Entity* p, double t) {
	if (active) {
		//Check that the particle has Finite Mass
		if (fabs((1 / p->mass)) < 1e-10) return ;
		//Apply the mass scaled gravity
		p->addForce(_gravity * p->mass);
	}
	
}