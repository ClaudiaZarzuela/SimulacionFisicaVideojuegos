#include "ParticleDragGenerator.h"
#include <iostream>

void ParticleDragGenerator::updateForce(Particle* particle, double t) {
	//Check that the particle has Finite Mass
	if (fabs(particle->_inv_mass) < 1e-10) return;
	if (insideBoundingBox(particle->_pose.p)) {
		//Compute the drag force
		Vector3 v = particle->getVel();
		//std::cout << v.x <<  " " << v.y << " " << v.z << std::endl;
		
		Vector3 dragF = _k1 * (_vel-v) + _k2 * (_vel-v).magnitude() * (_vel - v);
		//Apply the drag force
		//std::cout << dragF.x << "\t" << dragF.y << "\t" << dragF.z << std::endl;
		particle->addForce(dragF);
	}
}
bool ParticleDragGenerator::insideBoundingBox(Vector3 pos) {
	return (pos.x >= _pos.x - _dim.x && pos.x <= _pos.x + _dim.x) && (pos.y >= _pos.y && pos.y <= _pos.y + _dim.y) && (pos.z >= _pos.z - _dim.z && pos.z <= _pos.z + _dim.z);
}