#include "SolidoRigido.h"
SolidoRigido::SolidoRigido(PxScene* gS, PxPhysics* gP, physx::PxTransform Pos, Vector3 LinearVel, Vector3 AngularVel, Vector3 scale, 
	double d,float Mass, Vector4 color,float time, std::string tShape, std::string type, bool ismodel):
	gScene(gS), gPhysics(gP), _linearVel(LinearVel), _angularVel(AngularVel), density(d),Entity(Pos.p, scale, type, tShape) {
	_pose = Pos;
	_scale = scale;
	_color = color;
	typeShape = tShape;

	PxMaterial* _material = gPhysics->createMaterial(0.5,0.5,0.5);
	if(typeShape == "BOX") _shape = gPhysics->createShape(PxBoxGeometry(_scale), &_material, true, (PxShapeFlag::eSCENE_QUERY_SHAPE || PxShapeFlag::eSIMULATION_SHAPE));
	else _shape = gPhysics->createShape(PxSphereGeometry(_scale.x), &_material, true, (PxShapeFlag::eSCENE_QUERY_SHAPE || PxShapeFlag::eSIMULATION_SHAPE));
	PxFilterData _filterData = PxFilterData(1, 1, 0, 0);
	_shape->setSimulationFilterData(_filterData);

	_dynamic = gPhysics->createRigidDynamic(_pose);

	_dynamic->attachShape(*_shape);

	_dynamic->setLinearVelocity(_linearVel);
	_vel = _linearVel;

	float _density = 0.01f;
	PxRigidBodyExt::updateMassAndInertia(*_dynamic, _density);
	_dynamic->setAngularVelocity(_angularVel);
	PxVec3 inertia = _dynamic->getMassSpaceInertiaTensor();
	inertia.x = 0.0f;
	_dynamic->setMassSpaceInertiaTensor(inertia);
	_dynamic->setMaxDepenetrationVelocity(3.0f);


	mass = _dynamic->getMass();
	_inv_mass = 1 / mass;
	esModelo = ismodel;
	maxTime = time;
	gScene->addActor(*_dynamic);
	if(!ismodel) renderItem = new RenderItem(_shape, _dynamic, _color);


}
SolidoRigido::SolidoRigido(PxScene* gS, PxPhysics* gP, physx::PxTransform Pos, Vector3 scale, Vector4 color, std::string tShape, std::string type, bool ismodel):Entity(Pos.p, scale, type, tShape){
	gScene = gS;
	gPhysics = gP;
	_pose = Pos;
	_scale = scale;
	_color = color;
	typeShape = tShape;
	PxMaterial* _material = gPhysics->createMaterial(0.5, 0.5, 0.5);
	if (typeShape == "BOX") _shape = gPhysics->createShape(PxBoxGeometry(_scale), &_material, true, (PxShapeFlag::eSCENE_QUERY_SHAPE || PxShapeFlag::eSIMULATION_SHAPE));
	else _shape = gPhysics->createShape(PxSphereGeometry(_scale.x / 2), &_material, true, (PxShapeFlag::eSCENE_QUERY_SHAPE || PxShapeFlag::eSIMULATION_SHAPE));
	PxFilterData _filterData = PxFilterData(1, 1, 0, 0);
	_shape->setSimulationFilterData(_filterData);
	_static = gPhysics->createRigidStatic(_pose);
	_static->attachShape(*_shape);
	gScene->addActor(*_static);
	mass = 10000000000000000000;
	_inv_mass = 0;
	_vel = { 0,0,0 };
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