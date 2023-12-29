#pragma once
#include "RenderUtils.hpp"
#include "InteractuableObject.h"
class Entity : public InteractuableObject
{
public:
	physx::PxTransform _pose;
	Vector3 _scale;
	physx::PxShape* _shape;
	RenderItem* renderItem = nullptr;
	Vector4 _color;
	float time = 0;
	float maxTime;
	bool alive = true;
	bool esModelo;
	Vector3 force = Vector3(0, 0, 0);
	float mass;
	float _inv_mass;
	Vector3 _vel;

	inline int getVolume() { return _scale.x * _scale.y * _scale.z; }
	inline int getHeight() { return _scale.y; }
	virtual void addForce(const Vector3& f) = 0;
	virtual bool generatesOnDeath() = 0;
	virtual void integrate(double t) = 0;
	virtual void setPosition(Vector3 Pos) = 0;
	virtual Vector3 getPosition() = 0;
	virtual void setVelocity(Vector3 Vel) = 0;
	bool isAlive() { return alive; }
	Entity(Vector3 pos, Vector3 scale):InteractuableObject(pos, scale.y, scale.x, scale.z){}
	virtual ~Entity(){}
};

