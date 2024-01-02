#include "MyItem.h"
MyItem::MyItem(bool ground, float pX, float pY, float pZ, float sX, float sY, float sZ,
	float staticFriction, float dynamicFriction, float restitution, PxScene* gScene, PxPhysics* gPhysics) {
	PxBoxGeometry _geometry = PxBoxGeometry(sX, sY, sZ);
	_material = gPhysics->createMaterial(staticFriction, dynamicFriction, restitution);
	_shape = gPhysics->createShape(_geometry, &_material, true, (PxShapeFlag::eSCENE_QUERY_SHAPE || PxShapeFlag::eSIMULATION_SHAPE));
	PxFilterData _filterData = PxFilterData(1, 1, 0, 0);
	_shape->setSimulationFilterData(_filterData);

	PxVec3 _posVect = {pX, pY, pZ};
	PxTransform _pose = PxTransform(PxIdentity);
	_pose.p = { pX, pY, pZ };

	if (ground) {
		_item = gPhysics->createRigidStatic(_pose);
	}
	else {
		_item = gPhysics->createRigidDynamic(_pose);
	}

	_item->attachShape(*_shape);

	if (!ground) {
		tuneBox();
	}

	gScene->addActor(*_item);
	renderItem = new RenderItem(_shape, _item, { 0.8,0.8,0.8,1 });
}

MyItem::~MyItem() {
	_item->release();
	_shape->release();
	_material->release();
	if (renderItem != nullptr) DeregisterRenderItem(renderItem);
}

void MyItem::tuneBox() {
	PxRigidDynamic* box = static_cast<PxRigidDynamic*>(_item);
	float density = 0.01f;
	PxRigidBodyExt::updateMassAndInertia(*box, density);
	PxVec3 inertia = box->getMassSpaceInertiaTensor();
	inertia.x = 0.0f;
	box->setMassSpaceInertiaTensor(inertia);
	box->setMaxDepenetrationVelocity(3.0f);
}
