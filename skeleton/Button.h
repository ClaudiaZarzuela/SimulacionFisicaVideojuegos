#pragma once
#include "SolidoRigido.h"
#include "InteractuableObject.h"
#include <list>

class GameSystem;
class LevelSystem;
extern bool changeMenu;
extern int actualMenu;
extern int levelIndex;
class Button : public InteractuableObject
{
public:
	enum Functions {
		STARTGAME = 0, LEVEL_1 = 1, LEVEL_2 = 2, LEVEL_3 = 3, LEVEL_4 = 4, LEVEL_5 = 5, LEVEL_6 = 6, LEVEL_7 = 7, LEVEL_8 = 8, DEFAULT = 9, RESTARTGAME = 10, BACK = 11, INSTRUCTIONS = 12
	};
	Functions function;
private:
	PxScene* gScene = nullptr;
	PxPhysics* gPhysics = nullptr;
	std::list<SolidoRigido*> _letters;
	SolidoRigido* obj = nullptr;
	LevelSystem* _levelSystem = nullptr;
	void startGame();
	void startLevel(int i);
	void instructions();

	void generateLetters() {
		switch (function) {
			case BACK: 
			_letters.push_back(new SolidoRigido(gScene, gPhysics, { 68.25,37.5,-75 }, { 0.5, 2, 0.1 }, { 0,0,0.5,1 }));
			_letters.push_back(new SolidoRigido(gScene, gPhysics, { 70.25,37.5,-75 }, { 0.5, 2, 0.1 }, { 0,0,0.5,1 }));

			break;
			case STARTGAME: 
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -15,7,-75 }, { 4, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -15,1,-75 }, { 3, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -18,0,-75 }, { 1, 6, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -9,2.95,-55 }, { 1, 2.91, 0.1 }, { 0,0,0.5,1 }));
				
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -7,1,-75 }, { 1, 7, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -5,-5,-75 }, { 2.5, 1, 0.1 }, { 0,0,0.5,1 }));
				
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 4,7,-75 }, { 3, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 4,1,-75 }, { 2.5, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 2,0,-75 }, { 1, 6, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 6,0,-75 }, { 1, 6, 0.1 }, { 0,0,0.5,1 }));

				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 14,-2,-75 }, { 1, 4, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 14,2,-75 }, { 4, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 17,5,-75 }, { 1, 3, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 11,5,-75 }, { 1, 3, 0.1 }, { 0,0,0.5,1 }));
				break;
			case LEVEL_1: 
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -61.5,14,-85 }, { 1, 6, 0.1 }, { 0,0,0.5,1 }));
				break;
			case LEVEL_2:  
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -19,14,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -23,11,-85 }, { 1, 4, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -19,8,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -15,17,-85 }, { 1, 4, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -19,20,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				break;
			case LEVEL_3:
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 19,14,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 19,8,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 23,14,-85 }, { 1, 6, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 19,20,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				break;
			case LEVEL_4:
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 62,14,-85 }, { 4, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 66,14,-85 }, { 1, 6, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 58,16.5,-85 }, { 1, 3.5, 0.1 }, { 0,0,0.5,1 }));
				break;
			case LEVEL_5:
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -61,-19,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -65,-16,-85 }, { 1, 4, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -61,-13,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -57,-22,-85 }, { 1, 4, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -61,-25,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				break;
			case LEVEL_6:
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -19,-19,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -23,-19,-85 }, { 1, 6, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -19,-13,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -15,-22,-85 }, { 1, 4, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -19,-25,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				break;
			case LEVEL_7:
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 19,-13,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 23,-20,-85 }, { 1, 6, 0.1 }, { 0,0,0.5,1 }));
				break;
			case LEVEL_8:
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 62,-13,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 62,-19,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 62,-25,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 66,-20,-85 }, { 1, 6, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 58,-20,-85 }, { 1, 6, 0.1 }, { 0,0,0.5,1 }));
				break;
			case DEFAULT:break;
			case RESTARTGAME:break;
		
		default: break;
		}
	}
public:
	Button(PxScene* gS, PxPhysics* gP, physx::PxTransform pos, float width, float height, Functions f, LevelSystem* _level, Vector4 _color = { 0.8,0.8,0.8,1 }):InteractuableObject(pos.p, height, width, 1){
		gScene = gS;
		gPhysics = gP;
		obj = new SolidoRigido(gS, gP, pos, { width, height, 0.1 }, _color);
		function = f;
		_levelSystem = _level;
		generateLetters();
	}

	Button(PxScene* gS, PxPhysics* gP, physx::PxTransform pos, SolidoRigido* s) :InteractuableObject(pos.p, s->_scale.x, s->_scale.y, s->_scale.z) {
		obj = s;
	}
	void startFunction();
	virtual ~Button() {
		if(obj != nullptr) delete(obj);
		for (auto it = _letters.begin(); it != _letters.end();) {
			delete(*it);
			it = _letters.erase(it);
		}
	}
	
};

