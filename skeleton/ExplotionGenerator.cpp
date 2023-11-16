#include "ExplotionGenerator.h"
void ExplotionGenerator::updateForce(Particle* p, double t) {
	//Check that the particle has Finite Mass
		if (fabs((1 / p->mass)) < 1e-10) return ;

		auto pos = p->_pose;
		auto dist = pos.p - origin;
		if (dist.magnitude() < R) {
			float intens = K / pow(dist.magnitude(),2);
			auto explosionForce = intens * dist * exp(-t / _t);
			p->addForce(explosionForce);
		}
}