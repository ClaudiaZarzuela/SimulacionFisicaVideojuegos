#include "Proyectil.h"
#include <iostream>
Proyectil::Proyectil(Types currentType) {
	switch (currentType) {
	case PISTOL:
		speedReal = 330.0f;
		speedSim = 45.0f;
		masaReal = 5.0f;
		break;
	case ARTILLERY:
		speedReal = 1800.0f;
		speedSim = 20.0f;
		masaReal = 12.0f;
		break;
	case FIREBALL:
		speedReal = 250.0f;
		speedSim = 10.0f;
		masaReal = 3.0f;
		break;
	case LASER:
		speedReal = 300000000.0f;
		speedSim = 100.0f;
		masaReal = 0.1f;
		break;
	}
}

void Proyectil::integrate(double t) {
	for each (Particle* p in particles) p->integrate(t);
}

void Proyectil::shoot(Vector3 dir, Vector3 pos) {
	particles.push_back(new Particle(pos, speedSim * dir, calculateGravity(dir), 0.998, calculateMass(dir), calculateGravity(dir), 5.0f));
}

Vector3 Proyectil::calculateGravity(Vector3 dir) {
	return Vector3(0, -9.8 * pow(speedSim * dir.magnitude() / speedReal * dir.magnitude(), 2), 0);
}

float Proyectil::calculateMass(Vector3 dir) {
	return masaReal * pow(speedReal * dir.magnitude() / speedSim * dir.magnitude(), 2);
}