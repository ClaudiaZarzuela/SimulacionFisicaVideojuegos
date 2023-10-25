#pragma once
#include "RenderUtils.hpp"

enum Type {
	NORMAL, FIREWORK
};
class Particle
{
public: 
	Particle(Vector3 Pos, Vector3 Vel, Vector3 A, float Damping, float Masa, Vector3 Gravedad, 
		     float Time, Vector4 color, bool esModelo = false, double scale = 0.5);
	~Particle();

	void integrate(double t);
	bool isAlive() { return alive; }
	virtual Particle* clone() const;
	void setPos(Vector3 p) { _pose = physx::PxTransform(p); }

	// Position in world space
	physx::PxTransform _pose;
	// Linear velocity in world space
	Vector3 _vel;
	// Linear acceleration in world space
	Vector3 a;
	// Shape of the particle
	physx::PxShape* forma;
	// Color of the particle
	Vector4 _color;
	Vector3 gravedad = Vector3(0,-10,0);

	float time = 0;
	float maxTime;
	float damping = 0.998;
	float masa;
	bool alive = true;
	Type type = NORMAL;
	bool esModelo;
	double scale;
	RenderItem* renderItem = nullptr;
};

