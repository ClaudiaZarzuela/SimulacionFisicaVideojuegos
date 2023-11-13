#include "GravityForceGenerator.h"
void GravityForceGenerator::updateForce(Particle* p, double t) {
	//Check that the particle has Finite Mass
	if (fabs(p->mass) < 1e-10) //ponia _inv_mass
		return;
	//Apply the mass scaled gravity
	p->addForce(_gravity * p->mass);
}