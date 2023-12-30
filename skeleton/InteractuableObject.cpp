#include "InteractuableObject.h"
bool InteractuableObject::insideBoundingBox(Vector3 posPointer, Vector3 _otherScale, Vector3 _myPos) {
	if(_type == "ENEMY")
		return (posPointer.x + _otherScale.x >= _myPos.x - width -1 && posPointer.x - _otherScale.x <= _myPos.x + width +1) &&
		(posPointer.y + _otherScale.y >= _myPos.y - height-1 && posPointer.y - _otherScale.y <= _myPos.y + height+1) &&
		(posPointer.z + _otherScale.z >= _myPos.z - length-1 && posPointer.z - _otherScale.z <= _myPos.z + length+1);
	else return (posPointer.x > _myPos.x - width && posPointer.x <= _myPos.x + width) &&
		(posPointer.y >= _myPos.y - height && posPointer.y <= _myPos.y + height) &&
		(posPointer.z > _myPos.z - length && posPointer.z <= _myPos.z + length);
}

bool InteractuableObject::insideBoundingBox(Vector3 pos) {
	return (pos.x > box.minX && pos.x <= box.maxX) && 
		(pos.y >= box.minY && pos.y <= box.maxY) && 
		(pos.z > box.minZ && pos.z <= box.maxZ);
}