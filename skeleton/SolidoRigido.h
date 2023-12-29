#pragma once
#include <PxPhysicsAPI.h>>
#include "Entity.h"
using namespace physx;
class SolidoRigido :public Entity
{
protected:
	PxScene* gScene = nullptr;
	PxPhysics* gPhysics = nullptr;
	PxRigidDynamic* _dynamic = nullptr;
	PxRigidStatic* _static = nullptr;
	Vector3 _linearVel, _angularVel;
	double density;
	
public:
	SolidoRigido(PxScene* gS, PxPhysics* gP, physx::PxTransform Pos, Vector3 LinearVel, Vector3 AngularVel, Vector3 scale, double d, float Mass,Vector4 color, float time, bool ismodel = false);
	SolidoRigido(PxScene* gS, PxPhysics* gP, physx::PxTransform Pos, Vector3 scale, Vector4 color,  bool ismodel = false);
	virtual ~SolidoRigido(){
		if (renderItem != nullptr) {
			DeregisterRenderItem(renderItem);
			
		}
		if(_dynamic != nullptr) _dynamic->release();
		if(_static != nullptr) _static->release();
	}
	virtual void addForce(const Vector3& f) override {
		if(_dynamic != nullptr)
			_dynamic->addForce(f); 
		
	}
	inline SolidoRigido* clone(){ return new SolidoRigido(gScene, gPhysics, _pose, _linearVel, _angularVel, _scale, density,mass, _color, maxTime); }
	inline void setDensity(double d) { density = d; }
	virtual void setPosition(Vector3 Pos) override{ _pose.p = Pos; _dynamic->setGlobalPose(_pose); }
	virtual void setVelocity(Vector3 Vel) override { _linearVel = Vel; _dynamic->setLinearVelocity(_linearVel); }
	virtual void integrate(double t)override;
	virtual bool generatesOnDeath()override { return false; }
	virtual Vector3 getPosition() { 
		if (_dynamic != nullptr) return _dynamic->getGlobalPose().p;
		else return _static->getGlobalPose().p;
	};
};

