#include "ParticleDragGenerator.h"
#include <iostream>

void ParticleDragGenerator::updateForce(Entity* particle, double t) {
	//Check that the particle has Finite Mass
	if (active) {
		if (fabs(1 / (particle->mass)) < 1e-10) return;
		if (insideBoundingBox(particle->getPosition())) {
			//Compute the drag force
			Vector3 v = particle->_vel;
			Vector3 dragF = _k1 * (_wind - v) + _k2 * (_wind - v).magnitude() * (_wind - v);
			particle->addForce(dragF);
		}
	}
}
bool ParticleDragGenerator::insideBoundingBox(Vector3 pos) {
	return (pos.x >= _pos.x - _dim.x && pos.x <= _pos.x + _dim.x) && (pos.y >= _pos.y && pos.y <= _pos.y + height) && (pos.z >= _pos.z - _dim.z && pos.z <= _pos.z + _dim.z);
}