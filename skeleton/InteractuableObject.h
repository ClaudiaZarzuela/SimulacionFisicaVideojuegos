#pragma once
#include "core.hpp"
class InteractuableObject
{
protected:
	Vector3 position;
	float height;
	float width;
	float length;

	struct BoundingBox {
		int minX, maxX;
		int minY, maxY;
		int minZ, maxZ;
	};
	BoundingBox box;

	InteractuableObject(Vector3 pos, float h, float w, float l) {
		position = pos;
		height = h;
		width = w;
		length = l;

		box.minX = pos.x - width / 2;
		box.maxX = pos.x + width / 2;

		box.minY = pos.y - height / 2;
		box.maxY = pos.y + height / 2;

		box.minZ = pos.z - length / 2;
		box.maxZ = pos.z + length / 2;
			
	}
public:
	bool insideBoundingBox(Vector3 pos);
};

