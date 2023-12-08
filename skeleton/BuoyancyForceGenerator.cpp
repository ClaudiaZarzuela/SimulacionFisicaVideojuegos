#include "BuoyancyForceGenerator.h"
void BuoyancyForceGenerator::updateForce(Entity* particle, double t) {
	if (fabs(particle->_inv_mass) < 1e-10) return;
	else {

		if (active) {
			float h = particle->_pose.p.y;
			float h0 = _liquid_particle->_pose.p.y;

			Vector3 f(0, 0, 0);
			float immersed = 0.0;
			if (h - h0 > particle->getHeight() * 0.5) {
				immersed = 0.0;
			}
			else if (h0 - h > particle->getHeight() * 0.5) {
				immersed = 1.0;
			}
			else {
				immersed = (h0 - h) / particle->getHeight() + 0.5;
			}

			f.y = _liquid_density * particle->getVolume() * immersed * 9.8;
			particle->addForce(f);

		}
	}
}