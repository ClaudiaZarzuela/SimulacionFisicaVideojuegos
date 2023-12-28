#include "LevelSystem.h"

void LevelSystem::startLevel1() {
	physx::PxTransform pos = { 0,-25,-100 };
	_nest = new Nest(gScene, gPhysics, { 0,-40,-100 });
	_objPorNivel.push_back(new SolidoRigido(gScene, gPhysics, pos, { 9, 10,2.5 }, { 1,1,1,1 }));
}