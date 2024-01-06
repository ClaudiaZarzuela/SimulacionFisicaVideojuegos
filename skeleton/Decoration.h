#pragma once
#include "SolidoRigido.h"
#include <list>
class Decoration : public SolidoRigido
{
public:
	enum TYPE_DECORATION {
		SNOWMAN = 0, TREE1 = 1, TREE2
	};
	std::list<SolidoRigido*> decorList;

	Decoration(PxScene* gS, PxPhysics* gP, physx::PxTransform pos, Vector3 scale, TYPE_DECORATION _type):SolidoRigido() {
		switch (_type) {
			case SNOWMAN:
				decorList.push_back(new SolidoRigido(gS, gP, pos, { 30 * scale.x, 5 * scale.y, 30 * scale.z }, { 1,1,1,1 }, "SPHERE"));
				decorList.push_back(new SolidoRigido(gS, gP, { pos.p.x,pos.p.y + (5 * scale.y) * 2,pos.p.z }, { 20 * scale.x, 5 * scale.y, 20 * scale.z }, { 1,1,1,1 }, "SPHERE"));
				decorList.push_back(new SolidoRigido(gS, gP, { pos.p.x,pos.p.y + (float)(5 * scale.y) * 3.3f,pos.p.z }, { 10 * scale.x, 5 * scale.y, 10 * scale.z }, { 1,1,1,1 }, "SPHERE"));
				//decorList.push_back(new SolidoRigido(gS, gP, { pos.p.x,pos.p.y + (float)(5 * scale.y) * 6.5f,pos.p.z + 2.5f}, {scale.x, (float)(scale.y/2.0f), 5* scale.z}, {1,0.5,0.5,1}));

				break;
			case TREE1: 
				decorList.push_back(new SolidoRigido(gS, gP, pos, { 30*scale.x, 5*scale.y, 30*scale.z }, { 0.1,1,0.1,1 }));
				decorList.push_back(new SolidoRigido(gS, gP, { pos.p.x,pos.p.y + (5 * scale.y) * 2,pos.p.z }, { 20 * scale.x, 5 * scale.y, 20 * scale.z }, { 0.3,1,0.3,1 }));
				decorList.push_back(new SolidoRigido(gS, gP, { pos.p.x,pos.p.y + (5 * scale.y) * 4,pos.p.z }, { 10 * scale.x, 5 * scale.y, 10 * scale.z }, { 0.5,1,0.5,1 }));
				decorList.push_back(new SolidoRigido(gS, gP, { pos.p.x,pos.p.y - (15 * scale.y),pos.p.z }, { 5 * scale.x, 10 * scale.y, 5 * scale.z }, { 0.3,0.3,0.2,1 }));
				
				break;
			case TREE2:
				decorList.push_back(new SolidoRigido(gS, gP, pos, { 20 * scale.x, 7 * scale.y, 20 * scale.z }, { 0,1,0,1 }));
				decorList.push_back(new SolidoRigido(gS, gP, { pos.p.x,pos.p.y + (7 * scale.y) * 2,pos.p.z }, { 10 * scale.x, 7 * scale.y, 10 * scale.z }, { 0.1,1,0.1,1 }));
				decorList.push_back(new SolidoRigido(gS, gP, { pos.p.x,pos.p.y + (7 * scale.y) * 4,pos.p.z }, { 7 * scale.x, 7 * scale.y, 7 * scale.z }, { 0.2,1,0.2,1 }));
				decorList.push_back(new SolidoRigido(gS, gP, { pos.p.x,pos.p.y - (17 * scale.y),pos.p.z }, { 5 * scale.x, 10 * scale.y, 5 * scale.z }, { 0.3,0.3,0.2,1 }));

				break;
			default:break;
		}
	}

	~Decoration() {
		for (auto it = decorList.begin(); it != decorList.end();) {
			delete(*it);
			it = decorList.erase(it);
		}
	};
};

