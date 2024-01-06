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
public:
	std::string _type;
	InteractuableObject(){}
	InteractuableObject(Vector3 pos, float h, float w, float l, std::string t = "NORMAL") {
		position = pos;
		height = h;
		width = w;
		length = l;
		_type = t;

		box.minX = pos.x - width;
		box.maxX = pos.x + width;

		box.minY = pos.y - height;
		box.maxY = pos.y + height;

		box.minZ = pos.z - length;
		box.maxZ = pos.z + length;
	}
	bool insideBoundingBox(Vector3 posPointer, Vector3 _otherScale, Vector3 _myPos);
	bool insideBoundingBox(Vector3 pos);
};

