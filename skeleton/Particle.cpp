#include "Particle.h"
#include <math.h>
Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 A, float Damping, float Masa, Vector3 Gravedad, float Time) {
	_vel = Vel;
	_pose = physx::PxTransform(Pos);
	a = A; 
	damping = Damping;
	masa = Masa;
	gravedad = Gravedad;
	maxTime = Time;

	forma = CreateShape(physx::PxSphereGeometry(1));
	_color = Vector4(float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), 1);
	renderItem = new RenderItem(forma, &_pose, _color);	
}

Particle::~Particle() {
	renderItem->release();
}
void Particle::integrate(double t) {
	if (alive) {
		// Update position
		_pose.p += _vel * t;

		// Update linear velocity
		_vel += a * t;

		// Impose drag (damping)
		_vel *= pow(damping, t);
		time += t;
		if(time > maxTime) alive = false;
	}
}
 Particle* Particle::clone() const {
	 return new Particle(_pose.p, _vel, a,damping, masa,gravedad, maxTime);
 }
