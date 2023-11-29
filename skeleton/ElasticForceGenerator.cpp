#include "ElasticForceGenerator.h"
void ElasticForceGenerator::updateForce(Particle* particle, double t) {
	/* Ten en cuenta que la �nica diferencia es que en las part�culas unidas mediante una
       goma el�stica la fuerza del muelle s�lo se aplica cuando la distancia entre ambas supera la
       distancia de reposo (cuando la goma se estira) pero no cuando es menor (la goma se encoje).*/

    Vector3 relative_pos_vector = _other->_pose.p - particle->_pose.p; //Vector que une los dos extremos del muelle
    if (relative_pos_vector.magnitude() > _resting_length) SpringForceGenerator::updateForce(particle, t);

}