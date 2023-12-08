#include "SolidoRigido.h"
SolidoRigido::SolidoRigido(PxScene* gS, PxPhysics* gP, physx::PxTransform Pos, Vector3 LinearVel, Vector3 AngularVel, Vector3 scale, double d, Vector4 color, bool ismodel):
	gScene(gS), gPhysics(gP), _linearVel(LinearVel), _angularVel(AngularVel), density(d),Entity() {
	_pose = Pos;
	_scale = scale;
	_color = color;
	_dynamic = gPhysics->createRigidDynamic(_pose);
	_dynamic->setLinearVelocity(_linearVel);
	_vel = _linearVel;
	_dynamic->setAngularVelocity(_angularVel);
	_shape = CreateShape(PxBoxGeometry(_scale));
	_dynamic->attachShape(*_shape);
	PxRigidBodyExt::updateMassAndInertia(*_dynamic, density);
	mass = _dynamic->getMass(); 
	_inv_mass = 1 / mass;
	gScene->addActor(*_dynamic);
	esModelo = ismodel;
	maxTime = 30.0;
	if(!ismodel) renderItem = new RenderItem(_shape, _dynamic, _color);
}
SolidoRigido::SolidoRigido(PxScene* gS, PxPhysics* gP, physx::PxTransform Pos, Vector3 scale, Vector4 color, bool ismodel):Entity(){
	gScene = gS;
	gPhysics = gP;
	_pose = Pos;
	_scale = scale;
	_color = color;
	_static = gPhysics->createRigidStatic(_pose);
	_shape = CreateShape(PxBoxGeometry(scale));
	_static->attachShape(*_shape);
	mass = 0;
	_inv_mass = 0;
	_vel = { 0,0,0 };
	gScene->addActor(*_static);
	esModelo = ismodel;
	maxTime = -1e-10;
	if (!ismodel) renderItem = new RenderItem(_shape, _static, _color);
}

void SolidoRigido::integrate(double t) {
	if (alive) {
		time += t;
		if (time > maxTime) alive = false;
	}
}