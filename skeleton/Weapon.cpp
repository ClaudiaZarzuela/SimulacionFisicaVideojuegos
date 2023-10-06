#include "Weapon.h"
#include <iostream>
Weapon::Weapon(Types currentType) {
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

void Weapon::integrate(double t) {
	for (auto it = particles.begin(); it != particles.end();) {
		if ((*it)->isAlive()) {
			(*it)->integrate(t); ++it;
		}
		else {
			delete(*it);
			it = particles.erase(it);
		}
	}
}

void Weapon::shoot(Vector3 dir, Vector3 pos) {
	particles.push_back(new Particle(pos, speedSim * dir, calculateGravity(dir), 0.998, calculateMass(dir), calculateGravity(dir), 20.0f));
}

Vector3 Weapon::calculateGravity(Vector3 dir) {
	return Vector3(0, -9.8 * pow(speedSim * dir.magnitude() / speedReal * dir.magnitude(), 2), 0);
}

float Weapon::calculateMass(Vector3 dir) {
	return masaReal * pow(speedReal * dir.magnitude() / speedSim * dir.magnitude(), 2);
}