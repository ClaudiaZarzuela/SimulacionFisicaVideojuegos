#include "Plane.h"

Plane::Plane(Vector3 pos, Vector3 Dimensions, Vector4 Col) : pose(physx::PxTransform(pos)) {
	physx::PxBoxGeometry planeGeo(Dimensions);
	physx::PxShape* shape = CreateShape(planeGeo);
	renderItem = new RenderItem(shape, &pose, Col);
}

Plane::~Plane() {
	renderItem->release();
}