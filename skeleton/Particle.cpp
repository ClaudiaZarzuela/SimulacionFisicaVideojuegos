#include "Particle.h"
#include <math.h>
Particle::Particle(Vector3 Pos, Vector3 Vel) {
	vel = Vel;
	pose = physx::PxTransform(Pos);
	shape = CreateShape(physx::PxSphereGeometry(5));
	color = Vector4(0, 0, 0, 0);
	renderItem = new RenderItem(shape, &pose, color);
	
}
Particle::~Particle() {
	renderItem->release();
}
void Particle::integrate(double t) {
	vel = vel * pow(damping, t);
	pose.p += vel * t;
}