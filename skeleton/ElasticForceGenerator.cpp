#include "ElasticForceGenerator.h"
void ElasticForceGenerator::updateForce(Particle* particle, double t) {
	/* Ten en cuenta que la única diferencia es que en las partículas unidas mediante una
       goma elástica la fuerza del muelle sólo se aplica cuando la distancia entre ambas supera la
       distancia de reposo (cuando la goma se estira) pero no cuando es menor (la goma se encoje).*/

    Vector3 relative_pos_vector = _other->_pose.p - particle->_pose.p; //Vector que une los dos extremos del muelle
    if (relative_pos_vector.magnitude() > _resting_length) SpringForceGenerator::updateForce(particle, t);

}