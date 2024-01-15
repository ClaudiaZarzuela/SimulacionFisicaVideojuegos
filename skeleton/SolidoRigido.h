#pragma once
#include <PxPhysicsAPI.h>>
#include "Entity.h"
using namespace physx;

/*
	Igual que antes pero se le ha añadido un identificador de objeto (enemigo, normal, player...) y un de forma (box o sphere). 
	Dependiendo de la forma se generará un sólido rígido u otro.

	TEn la constructora tambien se les añade nuevo:
		- un material para hacerlos inelásticos ya que de base nvidia genera un mundo elástico
		- un PxFilterData para mejorar las colisiones entre solidos rigidos
		- un tensor de inercia con valor en la x a 0 para bloquear la rotacion en ese eje y simular un mundo en 2D
		- setMaxDepenetrationVelocity(), el cual hace que las colisiones se detecten a mayor distancia y mejore las colisiones

	El método changeForm() devuelve un nuevo solido rigido haciendo un clon del anterior pero variando su forma.
*/
class SolidoRigido :public Entity
{
public:
	PxRigidDynamic* _dynamic = nullptr;
protected:
	PxScene* gScene = nullptr;
	PxPhysics* gPhysics = nullptr;
	PxRigidStatic* _static = nullptr;
	Vector3 _linearVel, _angularVel;
	double density;

	
public:
	SolidoRigido() :Entity() {};
	SolidoRigido(PxScene* gS, PxPhysics* gP, physx::PxTransform Pos, Vector3 LinearVel, Vector3 AngularVel, Vector3 scale, double d, float Mass,Vector4 color, float time, std::string tShape = "BOX", std::string type = "NORMAL", bool ismodel = false);
	SolidoRigido(PxScene* gS, PxPhysics* gP, physx::PxTransform Pos, Vector3 scale, Vector4 color, std::string tShape = "BOX", std::string type = "NORMAL",  bool ismodel = false);
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
	virtual SolidoRigido* changeForm()override;
	virtual Vector3 getPosition() { 
		if (_dynamic != nullptr) return _dynamic->getGlobalPose().p;
		else return _static->getGlobalPose().p;
	};
};

