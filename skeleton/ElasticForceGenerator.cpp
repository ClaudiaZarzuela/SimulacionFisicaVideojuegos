#include "ElasticForceGenerator.h"
void ElasticForceGenerator::updateForce(Particle* particle, double t) {
    Vector3 relative_pos_vector = _other->_pose.p - particle->_pose.p; //Vector que une los dos extremos del muelle
    if (relative_pos_vector.magnitude() > _resting_length) SpringForceGenerator::updateForce(particle, t);

}