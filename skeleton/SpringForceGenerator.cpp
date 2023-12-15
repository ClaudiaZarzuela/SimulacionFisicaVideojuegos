#include "SpringForceGenerator.h"

SpringForceGenerator::SpringForceGenerator(double k, double resting_length, Particle* other) {
	_name = "SPRING";
	_k = k;
	_resting_length = resting_length;
	_other = other;
}

void SpringForceGenerator::updateForce(Entity* particle, double t) {

	Vector3 relative_pos_vector = _other->_pose.p - particle->getPosition();
	Vector3 force;

	const float length = relative_pos_vector.normalize(); 
	const float delta_x = length - _resting_length;

	force = relative_pos_vector * delta_x * _k;

	particle->addForce(force);
}