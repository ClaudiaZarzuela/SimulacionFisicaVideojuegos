#pragma once
#include "RenderUtils.hpp"
class Plane {
public:
	Plane(Vector3 pos, Vector3 Dimensions, Vector4 Color = { 0,0,0,1 });
	~Plane();
private:
	physx::PxTransform pose;
	RenderItem* renderItem;
};