#include "Particle.h"
#include <math.h>
Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 A, float Damping, float Masa, Vector3 Gravedad, float Time) {
	vel = Vel;
	pos = physx::PxTransform(Pos);
	a = A; 
	damping = Damping;
	masa = Masa;
	gravedad = Gravedad;
	maxTime = Time;

	forma = CreateShape(physx::PxSphereGeometry(1));
	color = Vector4(0, 0, 0, 0);
	renderItem = new RenderItem(forma, &pos, color);	
}
Particle::~Particle() {
	renderItem->release();
}
void Particle::integrate(double t) {
	if (alive) {
		// Update position
		pos.p += vel * t;

		// Update linear velocity
		vel += a * t;

		// Impose drag (damping)
		vel *= pow(damping, t);
		time += t;
		if(time > maxTime) alive = false;
	}
}