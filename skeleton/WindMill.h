#pragma once
#include "SolidoRigido.h"
#include "ParticleDragGenerator.h"
#include <list>

/*
	Clase encargada de generar los ventiladores: solidos rígidos estáticos con una velocidad angular contante ya que no les afecta ninguna otra fuerza y tiene el damping angular a 0.

	Esta clase tiene un metodo activate() que permite activar y deactivarlo añadiendo o quitando velocidad angular.
*/
class WindMill
{
public:
	RenderItem* renderItem = nullptr;
	PxRigidDynamic* dyn = nullptr;
	physx::PxShape* _shapeDyn;
	ParticleDragGenerator* _myWind = nullptr;
	PxMaterial* m = nullptr;
	bool active = true;
	WindMill(PxScene* gS, PxPhysics* gP, physx::PxTransform pos, ParticleDragGenerator* wind, bool act) {
		active = act;
		_myWind = wind;
		_myWind->active = active;
		dyn = gP->createRigidDynamic(pos);
		m = gP->createMaterial(0.5f, 0.5f, 0.6f);
		_shapeDyn = gP->createShape(PxBoxGeometry(0.01f, 1, 3),&m, true);
		dyn->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
		dyn->setAngularDamping(0.f);
		gS->addActor(*dyn);
		dyn->setMass(0.f);
		dyn->setMassSpaceInertiaTensor(PxVec3(0.f));
		renderItem = new RenderItem(_shapeDyn, dyn, {1,1,1,1});
		
	}

	void activate() {
		if (active) { dyn->setAngularVelocity(PxVec3(0.f, 0.f, 0.f)); }
		else { dyn->setAngularVelocity(PxVec3(5.f, 0.f, 0.f)); }
		active = !active;
		_myWind->activateForce();
	}
	virtual ~WindMill() {
		 _shapeDyn->release();
		 m->release();
		 dyn->release();
		DeregisterRenderItem(renderItem);
		delete(renderItem);
	}
};

