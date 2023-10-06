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

Particle::Particle(Vector3 Pos, Vector3 Vel, Vector3 A, float Damping) {
	vel = Vel;
	pos = physx::PxTransform(Pos);
	a = A;
	damping = Damping;

	forma = CreateShape(physx::PxSphereGeometry(1));
	color = Vector4(0, 0, 0, 0);
	renderItem = new RenderItem(forma, &pos, color);
}

Particle::Particle(Vector3 Pos, Vector3 Vel) {
	vel = Vel;
	pos = physx::PxTransform(Pos);

	forma = CreateShape(physx::PxSphereGeometry(1));
	color = Vector4(0, 0, 0, 0);
	renderItem = new RenderItem(forma, &pos, color);	
}
Particle::~Particle() {
	renderItem->release();
}
void Particle::integrate(double t) {

#pragma region Apartado 1
	pos.p += vel * t;
#pragma endregion

#pragma region Apartado 2
	/*pos.p += vel * t;
	vel += a * t;
	vel *= pow(damping, t);
	time += t;*/
	
#pragma endregion

#pragma region Apartado 3
	/*if (alive) {
		// Update position
		pos.p += vel * t;

		// Update linear velocity
		vel += a * t;

		// Impose drag (damping)
		vel *= pow(damping, t);
		time += t;
		if(time > maxTime) alive = false;
	}*/
#pragma endregion
	
	
}