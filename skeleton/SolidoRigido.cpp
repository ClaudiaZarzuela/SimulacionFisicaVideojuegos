#include "SolidoRigido.h"
SolidoRigido::SolidoRigido(PxScene* gS, PxPhysics* gP, physx::PxTransform Pos, Vector3 LinearVel, Vector3 AngularVel, Vector3 scale, 
	double d,float Mass, Vector4 color,float time, std::string tShape, std::string type, bool ismodel):
	gScene(gS), gPhysics(gP), _linearVel(LinearVel), _angularVel(AngularVel), density(d),Entity(Pos.p, scale, type, tShape) {
	_pose = Pos;
	_scale = scale;
	_color = color;
	typeShape = tShape;
	_dynamic = gPhysics->createRigidDynamic(_pose);
	gScene->addActor(*_dynamic);
	_dynamic->setLinearVelocity(_linearVel);
	_vel = _linearVel;
	_dynamic->setAngularVelocity(_angularVel);
	_dynamic->setAngularDamping(2.0f);
	_dynamic->setLinearDamping(1.0f);
	PxRigidBodyExt::updateMassAndInertia(*_dynamic, density);
	PxMaterial*m = gP->createMaterial(0.0000000000000000001f, 0.0000000000000000001f, 1.0f);
	if(typeShape == "BOX") _shape = CreateShape(PxBoxGeometry(_scale), m);
	else _shape = CreateShape(PxSphereGeometry(_scale.x), m);
	_shape->setContactOffset(0.2);
	_dynamic->attachShape(*_shape);
	mass = _dynamic->getMass();
	_inv_mass = 1 / mass;
	esModelo = ismodel;
	maxTime = time;
	if(!ismodel) renderItem = new RenderItem(_shape, _dynamic, _color);
}
SolidoRigido::SolidoRigido(PxScene* gS, PxPhysics* gP, physx::PxTransform Pos, Vector3 scale, Vector4 color, std::string tShape, std::string type, bool ismodel):Entity(Pos.p, scale, type, tShape){
	gScene = gS;
	gPhysics = gP;
	_pose = Pos;
	_scale = scale;
	_color = color;
	typeShape = tShape;
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

SolidoRigido* SolidoRigido::changeForm(){
	SolidoRigido* aux;
	if (typeShape == "BOX") aux = new SolidoRigido(gScene, gPhysics, { this->getPosition().x,this->getPosition().y,this->getPosition().z }, _linearVel, _angularVel, _scale, density, mass, _color, maxTime, "SPHERE", _type, esModelo);
	else aux = new SolidoRigido(gScene, gPhysics, { this->getPosition().x,this->getPosition().y,this->getPosition().z }, _linearVel, _angularVel, _scale, density, mass, _color, maxTime, "BOX", _type, esModelo);
	return aux;
}

void SolidoRigido::integrate(double t) {
	if (alive) {
		time += t;
		if (time > maxTime) alive = false;
	}
}