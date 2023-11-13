#include "Particle.h"
#include <math.h>
#include "FireworkGenerator.h"
Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 A, float Damping, float Masa, Vector3 Gravedad, float Time, Vector4 color, bool esMod, double s) {
	_vel = Vel;
	_pose = physx::PxTransform(Pos);
	a = A; 
	damping = Damping;
	mass = Masa;
	gravedad = Gravedad;
	maxTime = Time;
	esModelo = esMod; 
	scale = s;
	forma = CreateShape(physx::PxSphereGeometry(scale));
	_color = color;
	if(!esModelo) renderItem = new RenderItem(forma, &_pose, _color);	
}


Particle::Particle(Vector3 Pos, Vector3 Vel, float Damping, float Masa, float Time, Vector4 color, bool esMod, double s) {
	_vel = Vel;
	_pose = physx::PxTransform(Pos);
	damping = Damping;
	mass = Masa;
	maxTime = Time;
	esModelo = esMod;
	scale = s;
	forma = CreateShape(physx::PxSphereGeometry(scale));
	_color = color;
	if (!esModelo) renderItem = new RenderItem(forma, &_pose, _color);
}

Particle::~Particle() {
	if(renderItem != nullptr)
		renderItem->release();
}
void Particle::integrate(double t) {
	if (alive) {
		// Get the accel considering the force accum
		Vector3 resulting_accel = force * mass;
		// Update linear velocity
		_vel += resulting_accel * t;
		// Impose drag (damping)
		_vel *= pow(damping, t);
		// Update position
		_pose.p += _vel * t;
		time += t;
		if(time > maxTime) alive = false;
		clearForce();
	}
}
Particle* Particle::clone() const {
	return new Particle(_pose.p, _vel, a, damping, mass, gravedad, maxTime, _color, false, scale);
}

bool Particle::generatesOnDeath() { return _gen != nullptr; }