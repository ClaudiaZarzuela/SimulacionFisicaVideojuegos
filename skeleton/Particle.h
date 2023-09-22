#pragma once
#include "RenderUtils.hpp"
class Particle
{
public: Particle(Vector3 Pos, Vector3 Vel);
	  ~Particle();

	  void integrate(double t);

private:
	Vector3 vel;
	physx::PxTransform pose;
	RenderItem* renderItem;
	physx::PxShape* shape;
	Vector4 color;
	double damping = 0.998;
};

