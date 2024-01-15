#pragma once
#include "SolidoRigido.h"
#include <list>

/*
Clase encargada de crear las decoraciones de los niveles. Cada decoración está creada por un conjunto de solidos rígidos estáticos con color.
Esta clase es puramente estética, ayudando a la inmersión del jugador y clarificando el objetivo y temática del juego.

Se crea cada objeto a mano y se mete a la lista decorList, la cuál facilita la destruccion de cada uno de estos objetos posteriormente. Solo se meten a la lista
los objetos de cada nivel.
*/
class Decoration : public SolidoRigido
{
public:
	enum TYPE_DECORATION {
		SNOWMAN = 0, TREE1 = 1, TREE2 = 2, CLOUDS = 3, NIGHTSKY = 4, SUNSETSKY = 5, CLOUDYSKY = 6, NORMALSKY = 7, SUNSETVIOLETESKY = 8
	};
	std::list<SolidoRigido*> decorList;

	//Creación de objetos
	Decoration(PxScene* gS, PxPhysics* gP, physx::PxTransform pos, Vector3 scale, TYPE_DECORATION _type):SolidoRigido() {
		switch (_type) {
			case SNOWMAN:
				decorList.push_back(new SolidoRigido(gS, gP, pos, { 30 * scale.x, 5 * scale.y, 30 * scale.z }, { 1,1,1,1 }, "SPHERE"));
				decorList.push_back(new SolidoRigido(gS, gP, { pos.p.x,pos.p.y + (5 * scale.y) * 2,pos.p.z }, { 20 * scale.x, 5 * scale.y, 20 * scale.z }, { 1,1,1,1 }, "SPHERE"));
				decorList.push_back(new SolidoRigido(gS, gP, { pos.p.x,pos.p.y + (float)(5 * scale.y) * 3.3f,pos.p.z }, { 10 * scale.x, 5 * scale.y, 10 * scale.z }, { 1,1,1,1 }, "SPHERE"));
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

			case CLOUDS:
				decorList.push_back(new SolidoRigido(gS, gP, pos, { scale.x, scale.y, scale.z }, { 255,255,255,1 }));
				break;

			case NIGHTSKY:
				decorList.push_back(new SolidoRigido(gS, gP, {-400,210,-500}, {scale.x,  scale.y,  scale.z}, {1,1,1,1}, "SPHERE"));
				decorList.push_back(new SolidoRigido(gS, gP, {-310,169,-400}, {scale.x-27,  scale.y-27,  scale.z}, {0,0,0,1}, "SPHERE"));
				decorList.push_back(new SolidoRigido(gS, gP, {0,0,-500}, {100000, 100000 , 0.01}, {0,0,0,1}));

				for (int i = 0; i < 20; ++i) {
					physx::PxTransform pos = { rand() % 800 - 400.0f, rand() % 400 -100.0f, -499.0f };
					decorList.push_back(new SolidoRigido(gS, gP, pos, {2,0.5f,0.01 }, {1,1,1,1}));
					decorList.push_back(new SolidoRigido(gS, gP, pos, {0.5f,4,0.01 }, {1,1,1,1}));

				}
				break;

			case SUNSETSKY:
				decorList.push_back(new SolidoRigido(gS, gP, { 0,280,-550 }, { 100000, 40 , 0.01 }, { 0.5,0.1,0.2,1 }));
				decorList.push_back(new SolidoRigido(gS, gP, { 0,240,-550 }, { 100000, 40 , 0.01 }, { 0.6,0.2,0.2,1 }));
				decorList.push_back(new SolidoRigido(gS, gP, { 0,200,-550 }, { 100000, 40 , 0.01 }, { 0.7,0.3,0.2,1 }));
				decorList.push_back(new SolidoRigido(gS, gP, { 0,160,-550 }, { 100000, 40 , 0.01 }, { 0.7,0.4,0.2,1 }));
				decorList.push_back(new SolidoRigido(gS, gP, { 0,120,-550 }, { 100000, 40 , 0.01 }, { 0.8,0.5,0.2,1 }));
				decorList.push_back(new SolidoRigido(gS, gP, { 0,0,-550 }, { 100000, 80 , 0.01 }, { 0.9,0.6,0.3,1 }));
				decorList.push_back(new SolidoRigido(gS, gP, { 0,-70,-570 }, { 200,200,200}, { 2,1,0,1 }, "SPHERE"));
				break;

			case CLOUDYSKY:
				decorList.push_back(new SolidoRigido(gS, gP, { 0,260,-500 }, { 100000, 40 , 0.01 }, { 0.2,0.2,0.2,1 }));
				decorList.push_back(new SolidoRigido(gS, gP, { 0,220,-500 }, { 100000, 40 , 0.01 }, { 0.3,0.3,0.3,1 }));
				decorList.push_back(new SolidoRigido(gS, gP, { 0,180,-500 }, { 100000, 40 , 0.01 }, { 0.4,0.4,0.4,1 }));
				decorList.push_back(new SolidoRigido(gS, gP, { 0,140,-500 }, { 100000, 40 , 0.01 }, { 0.5,0.5,0.5,1 }));
				decorList.push_back(new SolidoRigido(gS, gP, { 0,100,-500 }, { 100000, 40 , 0.01 }, { 0.6,0.6,0.6,1 }));
				decorList.push_back(new SolidoRigido(gS, gP, { 0,0,-500 }, { 100000, 80 , 0.01 }, { 0.7,0.7,0.7,1 }));
				break;

			case NORMALSKY:
				for (int i = 0; i < 5; ++i) {
					physx::PxTransform poss = {-400.0f +i*200,  rand() % 300 - 50.0f, -499.0f };
					decorList.push_back(new SolidoRigido(gS, gP, poss, {50,10,50}, {4, 3,3,1 }));
					decorList.push_back(new SolidoRigido(gS, gP, {poss.p.x,poss.p.y + 20.0f,poss.p.z}, {40,10,40}, {4,3,3,1}));
				}
				decorList.push_back(new SolidoRigido(gS, gP, { 0,0,-500 }, { 100000, 100000 , 0.01 }, { 0.7,0.8,0.9,1 }));
				break;

			case SUNSETVIOLETESKY:

				for (int i = 0; i < 20; ++i) {
					physx::PxTransform pos = { rand() % 800 - 400.0f, rand() % 400 - 100.0f, -499.0f };
					decorList.push_back(new SolidoRigido(gS, gP, pos, { 2,0.5f,0.01 }, { 1,1,1,1 }));
					decorList.push_back(new SolidoRigido(gS, gP, pos, { 0.5f,4,0.01 }, { 1,1,1,1 }));

				}

				decorList.push_back(new SolidoRigido(gS, gP, { 0,260,-500 }, { 100000, 40 , 0.01 }, { 0.45,0.30,2,1 }));
				decorList.push_back(new SolidoRigido(gS, gP, { 0,220,-500 }, { 100000, 40 , 0.01 }, { 0.45,0.35,2,1 }));
				decorList.push_back(new SolidoRigido(gS, gP, { 0,180,-500 }, { 100000, 40 , 0.01 }, { 0.45,0.40,2,1 }));
				decorList.push_back(new SolidoRigido(gS, gP, { 0,140,-500 }, { 100000, 40 , 0.01 }, { 0.45,0.45,2,1 }));
				decorList.push_back(new SolidoRigido(gS, gP, { 0,100,-500 }, { 100000, 40 , 0.01 }, { 0.45,0.50,2,1 }));
				decorList.push_back(new SolidoRigido(gS, gP, { 0,0,-500 }, { 100000, 80 , 0.01 }, { 0.45,0.55,2,1 }));
				decorList.push_back(new SolidoRigido(gS, gP, { -400,210,-500 }, { 70,70,5 }, { 255,255,255,1 }, "SPHERE"));
				break;

			default:break;
		}
	}

	//Destructora
	~Decoration() {
		for (auto it = decorList.begin(); it != decorList.end();) {
			delete(*it);
			it = decorList.erase(it);
		}
	};
};

