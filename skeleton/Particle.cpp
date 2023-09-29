#include "Particle.h"
#include <math.h>
Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 A, float Damping, float Masa, float Gravedad) {
	vel = Vel;
	pos = physx::PxTransform(Pos);
	a = A; 
	damping = Damping;
	masa = Masa;
	gravedad = Gravedad;

	forma = CreateShape(physx::PxSphereGeometry(5));
	color = Vector4(0, 0, 0, 0);
	renderItem = new RenderItem(forma, &pos, color);


	/*Gs = gr(vs/vr)^2*/
	
}
Particle::~Particle() {
	renderItem->release();
}
void Particle::integrate(double t) {
	// Update position
	pos.p += vel * t;

	// Update linear velocity
	vel += a * t;

	// Impose drag (damping)
	vel *= pow(damping, t);
}