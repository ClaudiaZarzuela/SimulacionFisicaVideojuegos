#include "SolidoRigido.h"
SolidoRigido::SolidoRigido(PxScene* gS, PxPhysics* gP, physx::PxTransform Pos, Vector3 LinearVel, Vector3 AngularVel, Vector3 scale, double d,float Mass, Vector4 color,float time, bool ismodel):
	gScene(gS), gPhysics(gP), _linearVel(LinearVel), _angularVel(AngularVel), density(d),Entity() {
	_pose = Pos;
	_scale = scale;
	_color = color;
	_dynamic = gPhysics->createRigidDynamic(_pose);
	gScene->addActor(*_dynamic);
	_dynamic->setLinearVelocity(_linearVel);
	_vel = _linearVel;
	_dynamic->setAngularVelocity(_angularVel);
	PxRigidBodyExt::updateMassAndInertia(*_dynamic, density);
	_shape = CreateShape(PxBoxGeometry(_scale));
	_dynamic->attachShape(*_shape);
	//_dynamic->setMass(Mass);
	mass = _dynamic->getMass();
	_inv_mass = 1 / mass;
	esModelo = ismodel;
	maxTime = time;
	if(!ismodel) renderItem = new RenderItem(_shape, _dynamic, _color);
}
SolidoRigido::SolidoRigido(PxScene* gS, PxPhysics* gP, physx::PxTransform Pos, Vector3 scale, Vector4 color, bool ismodel):Entity(){
	gScene = gS;
	gPhysics = gP;
	_pose = Pos;
	_scale = scale;
	_color = color;
	_static = gPhysics->createRigidStatic(_pose);
	_shape = CreateShape(PxBoxGeometry(_scale));
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