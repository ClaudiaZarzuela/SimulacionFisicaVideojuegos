#pragma once
#include "RenderUtils.hpp"
class Particle
{
public: 
	//Apartado 1
	Particle(Vector3 Pos, Vector3 Vel);

	//Apartado 2
	Particle(Vector3 Pos, Vector3 Vel, Vector3 A, float Damping);

	//Apartado 3
	Particle(Vector3 Pos, Vector3 Vel, Vector3 A, float Damping, float Masa, Vector3 Gravedad, float Time);
	
	~Particle();

	void integrate(double t);
	bool isAlive() { return alive; }

private:
	// Position in world space
	physx::PxTransform pos;
	// Linear velocity in world space
	Vector3 vel;
	// Linear acceleration in world space
	Vector3 a;
	// Shape of the particle
	physx::PxShape* forma;
	// Color of the particle
	Vector4 color;
	Vector3 gravedad;

	float time = 0;
	float maxTime;
	float damping = 0.998;
	float masa;
	bool alive = true;
	RenderItem* renderItem;
};

