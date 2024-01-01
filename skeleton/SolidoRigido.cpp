#include "SolidoRigido.h"
SolidoRigido::SolidoRigido(PxScene* gS, PxPhysics* gP, physx::PxTransform Pos, Vector3 LinearVel, Vector3 AngularVel, Vector3 scale, 
	double d,float Mass, Vector4 color,float time, std::string tShape, std::string type, bool ismodel):
	gScene(gS), gPhysics(gP), _linearVel(LinearVel), _angularVel(AngularVel), density(d),Entity(Pos.p, scale, type, tShape) {
	_pose = Pos;
	_scale = scale;
	_color = color;
	typeShape = tShape;
	_dynamic = gPhysics->createRigidDynamic(_pose);
	_dynamic->setLinearVelocity(_linearVel);
	_vel = _linearVel;
	PxRigidBodyExt::updateMassAndInertia(*_dynamic, density);
	_dynamic->setAngularVelocity(_angularVel);
	if (typeShape == "BOX") {
		_dynamic->setAngularDamping(2.0f);
		_dynamic->setMaxAngularVelocity(0);
		_dynamic->setLinearDamping(1.0f);
	}
	else {
		_dynamic->setAngularDamping(4.0f);
		_dynamic->setLinearDamping(2.0f);
	}
	PxMaterial* m = gP->createMaterial(0, 0, 0);
	if(typeShape == "BOX") _shape = CreateShape(PxBoxGeometry(_scale),m);
	else _shape = CreateShape(PxSphereGeometry(_scale.x));
	_shape->setContactOffset(0.05);
	_dynamic->attachShape(*_shape);
	mass = _dynamic->getMass();
	_inv_mass = 1 / mass;
	esModelo = ismodel;
	maxTime = time;
	gScene->addActor(*_dynamic);
	gScene->setBounceThresholdVelocity(100000000);
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
	PxMaterial* m = gP->createMaterial(0, 0, 0);
	_shape = CreateShape(PxBoxGeometry(_scale),m);
	_shape->setContactOffset(0.05);
	_static->attachShape(*_shape);
	mass = 10000000000000000000;
	_inv_mass = 0;
	_vel = { 0,0,0 };
	esModelo = ismodel;
	maxTime = -1e-10;
	gScene->addActor(*_static);
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