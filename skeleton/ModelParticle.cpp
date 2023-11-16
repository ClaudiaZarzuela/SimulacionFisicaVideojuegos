#include "ModelParticle.h"

Vector3 ModelParticle::calculateGravity(Types currentType, Vector3 dir) {
	
	return Vector3(0, -9.8 * pow(currentType.speedSim * dir.magnitude() / currentType.speedReal * dir.magnitude(), 2), 0);
}

float ModelParticle::calculateMass(Types currentType, Vector3 dir) {
	return currentType.masaReal * pow(currentType.speedReal * dir.magnitude() / currentType.speedSim * dir.magnitude(), 2);
}

//Particle* ModelParticle::createParticle(Types currentType, float lifeTime, Vector3 pos, Vector3 dir) {
//	return new Particle(pos, currentType.speedSim * dir,  0.998, calculateMass(currentType,dir), 3.0f, Vector4(float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), 1)));
//}