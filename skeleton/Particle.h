#pragma once
#include "RenderUtils.hpp"
#include <list>
class FireworkGenerator;

class Particle
{
public: 
	Particle(Vector3 Pos, Vector3 Vel, Vector3 A, float Damping, float Masa, Vector3 Gravedad, 
		float Time, Vector4 color, bool esModelo = false, double scale = 0.5);
	Particle(Vector3 Pos, Vector3 Vel, float Damping, float Masa, float Time, Vector4 color, bool esMod, double scale = 0.5);
	~Particle();

	void integrate(double t);
	bool isAlive() { return alive; }
	virtual Particle* clone() const;
	void setPos(Vector3 p) { _pose = physx::PxTransform(p); }
	bool generatesOnDeath();
	inline Vector3 getVel() { return _vel; }
	virtual std::list<Particle*> explode() { return std::list<Particle*>(); }
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
	float mass;
	//float _inv_mass;
	bool alive = true;
	bool esModelo;
	double scale;
	Vector3 force = Vector3(0, 0, 0);
	// Clears accumulated force
	inline void clearForce() { force *= 0.0; }
	// Add force to apply in next integration only
	inline void addForce(const Vector3& f) { force += f; }
	RenderItem* renderItem = nullptr;
	FireworkGenerator* _gen = nullptr;
};

