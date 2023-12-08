#pragma once
#include <PxPhysicsAPI.h>>
#include "Entity.h"
using namespace physx;
class SolidoRigido :public Entity
{
private:
	PxScene* gScene = nullptr;
	PxPhysics* gPhysics = nullptr;
	PxRigidDynamic* _dynamic = nullptr;
	PxRigidStatic* _static = nullptr;
	Vector3 _linearVel, _angularVel;
	double density;
	
public:
	SolidoRigido(PxScene* gS, PxPhysics* gP, physx::PxTransform Pos, Vector3 LinearVel, Vector3 AngularVel, Vector3 scale, double d, Vector4 color, bool ismodel = false);
	SolidoRigido(PxScene* gS, PxPhysics* gP, physx::PxTransform Pos, Vector3 scale, Vector4 color, bool ismodel = false);
	~SolidoRigido(){
		if (renderItem != nullptr)
			renderItem->release();
	}
	virtual void addForce(const Vector3& f) override { _dynamic->addForce(f);}
	inline SolidoRigido* clone(){ return new SolidoRigido(gScene, gPhysics, _pose, _linearVel, _angularVel, _scale, density, _color); }
	inline void setDensity(double d) { density = d; }
	virtual void setPosition(Vector3 Pos) override{ _pose.p = Pos; _dynamic->setGlobalPose(_pose); }
	virtual void setVelocity(Vector3 Vel) override { _linearVel = Vel; _dynamic->setLinearVelocity(_linearVel); }
	virtual void integrate(double t)override;
	virtual bool generatesOnDeath()override { return true; }
};

