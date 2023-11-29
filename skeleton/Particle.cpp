#include "Particle.h"
#include <math.h>
#include "FireworkGenerator.h"
#include <iostream>
const float Particle::RANDOM = float(rand() % 256 / 255.0f);
Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 A, float Damping, float Masa, Vector3 Gravedad, float Time, Vector4 color, bool esMod, double s, GEOMETRY geometria) {
	_myGeometry = geometria;
	_vel = Vel;
	_pose = physx::PxTransform(Pos);
	a = A; 
	damping = Damping;
	mass = Masa;
	_inv_mass = 1 / mass;
	gravedad = Gravedad;
	maxTime = Time;
	esModelo = esMod; 
	scale = s;
	addGeometry();
	_color = { float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), 1 };
	if(!esModelo) renderItem = new RenderItem(forma, &_pose, _color);	
}


Particle::Particle(Vector3 Pos, Vector3 Vel, float Damping, float Masa, float Time, bool esMod, Vector4 color, double s, GEOMETRY geometria) {
	_myGeometry = geometria;
	_vel = Vel;
	_pose = physx::PxTransform(Pos);
	damping = Damping;
	mass = Masa;
	_inv_mass = 1 / mass;
	maxTime = Time;
	esModelo = esMod;
	scale = s;
	addGeometry();
	_color = { float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), 1 };
	if (!esModelo) renderItem = new RenderItem(forma, &_pose, _color);
}
Particle::Particle(Vector3 Pos, Vector3 Vel, float Masa, float Time, GEOMETRY geometria, Vector4 color, bool esMod, double s) {
	_myGeometry = geometria;
	_vel = Vel;
	_pose = physx::PxTransform(Pos);
	mass = Masa;
	_inv_mass = 1 / mass;
	damping = 0.85;
	maxTime = Time;
	esModelo = esMod;
	scale = s;
	addGeometry();
	_color = { float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), 1 };
	if (!esModelo) renderItem = new RenderItem(forma, &_pose, _color);
}

Particle::~Particle() {
	if(renderItem != nullptr)
		renderItem->release();
}
void Particle::integrate(double t) {
	if (alive) {
		// Get the accel considering the force accum
		Vector3 resulting_accel = force * _inv_mass;
		// Update linear velocity
		_vel += resulting_accel * t;
		// Impose drag (damping)
		_vel *= powf(damping, t);
		// Update position
		_pose.p += _vel * t;
		time += t;
		if(time > maxTime) alive = false;
		clearForce();
	}
}
Particle* Particle::clone() const {
	return new Particle(_pose.p, _vel, damping, mass, maxTime, false, _color, scale);
}

bool Particle::generatesOnDeath() { return _gen != nullptr; }