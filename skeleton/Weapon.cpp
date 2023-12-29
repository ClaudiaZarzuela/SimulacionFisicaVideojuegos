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

Particle* Weapon::shoot(Vector3 dir, Vector3 pos) {
	return new Particle(pos, speedSim * dir, calculateGravity(dir), 0.998, calculateMass(dir), calculateGravity(dir), 5.0f, Vector4(0.2, 0.5, 0.8, 1), false, { 0.1,0.1,0.1 });
}

Vector3 Weapon::calculateGravity(Vector3 dir) {
	return Vector3(0, -9.8 * pow(speedSim * dir.magnitude() / speedReal * dir.magnitude(), 2), 0);
}

float Weapon::calculateMass(Vector3 dir) {
	return masaReal * pow(speedReal * dir.magnitude() / speedSim * dir.magnitude(), 2);
}