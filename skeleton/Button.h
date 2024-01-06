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
		STARTGAME = 0, LEVEL_1 = 1, LEVEL_2 = 2, LEVEL_3 = 3, LEVEL_4 = 4, LEVEL_5 = 5, LEVEL_6 = 6,DEFAULT = 9, RESTARTGAME = 10, BACK = 11, INSTRUCTIONS = 12, WIND1 = 13, WIND2 = 14
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



				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -24,30,-75 }, { 1, 6, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -22,32,-75 }, { 1, 1, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -20,30,-75 }, { 1, 1, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -18,28,-75 }, { 1, 1, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -16,30,-75 }, { 1, 6, 0.1 }, { 1,1,1,1 }));


				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -9,30,-75 }, { 1, 6, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -5,35,-75 }, { 3, 1, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -7,30,-75 }, { 1, 1, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -5,25,-75 }, { 3, 1, 0.1 }, { 1,1,1,1 }));

				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 9,34,-85 }, { 5, 1, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 5,37,-85 }, { 1, 4, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 9,40,-85 }, { 5, 1, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 13,31,-85 }, { 1, 4, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 9,28,-85 }, { 5, 1, 0.1 }, { 1,1,1,1 }));

				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 23,30,-75 }, { 1, 6, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 23,35,-75 }, { 5, 1, 0.1 }, { 1,1,1,1 }));


				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 50,-33,-85 }, { 2, 0.5, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 49,-32,-85 }, { 0.5, 0.5, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 50,-31,-85 }, { 0.5, 0.5, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 51,-30,-85 }, { 0.5, 0.5,0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 50,-29,-85 }, { 2, 0.5, 0.1 }, { 0,0,0.5,1 }));

				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 60,-23,-85 }, { 2, 0.5, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 59,-22,-85 }, { 0.5, 0.5, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 60,-21,-85 }, { 0.5, 0.5, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 61,-20,-85 }, { 0.5, 0.5,0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 60,-19,-85 }, { 2, 0.5, 0.1 }, { 0,0,0.5,1 }));

				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 55,-28,-85 }, { 2, 0.5, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 54,-27,-85 }, { 0.5, 0.5, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 55,-26,-85 }, { 0.5, 0.5, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 56,-25,-85 }, { 0.5, 0.5,0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 55,-24,-85 }, { 2, 0.5, 0.1 }, { 0,0,0.5,1 }));


				break;
			case LEVEL_1: 


				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -29,30,-75 }, { 1, 6, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -25,25,-75 }, { 3, 1, 0.1 }, { 1,1,1,1 }));

				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -19,30,-75 }, { 1, 6, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -15,35,-75 }, { 3, 1, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -17,30,-75 }, { 1, 1, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -15,25,-75 }, { 3, 1, 0.1 }, { 1,1,1,1 }));

				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -9,34,-75 }, { 1, 2, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -7,30,-75 }, { 1, 2, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -5,26,-75 }, { 1, 2, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -3,30,-75 }, { 1, 2, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -1,34,-75 }, { 1, 2, 0.1 }, { 1,1,1,1 }));

				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 3,30,-75 }, { 1, 6, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 6,35,-75 }, { 3, 1, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 5,30,-75 }, { 1, 1, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 6,25,-75 }, { 3, 1, 0.1 }, { 1,1,1,1 }));

				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 12,30,-75 }, { 1, 6, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 16,25,-75 }, { 3, 1, 0.1 }, { 1,1,1,1 }));

				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 30,36,-90 }, { 5, 1, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 26,39,-90 }, { 1, 4, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 30,42,-90 }, { 5, 1, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 34,33,-90 }, { 1, 4, 0.1 }, { 1,1,1,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 30,30,-90 }, { 5, 1, 0.1 }, { 1,1,1,1 }));

				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -46.5,4,-85 }, { 1, 6, 0.1 }, { 0,0,0.5,1 }));
				break;
			case LEVEL_2:  
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 0,4,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -4,1,-85 }, { 1, 4, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 0,-2,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 4,7,-85 }, { 1, 4, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 0,10,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				break;
			case LEVEL_3:
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 48,4,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 48,-2,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 52,4,-85 }, { 1, 6, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 48,10,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				break;
			case LEVEL_4:
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -46,-29,-85 }, { 4, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -42.5,-29,-85 }, { 1, 6, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -50.5,-26.5,-85 }, { 1, 3.5, 0.1 }, { 0,0,0.5,1 }));
				break;
			case LEVEL_5:
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 0,-29,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { -4,-26,-85 }, { 1, 4, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 0,-23,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 4,-32,-85 }, { 1, 4, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 0,-35,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				break;
			case LEVEL_6:
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 47,-29,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 43,-29,-85 }, { 1, 6, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 47,-23,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 51,-32,-85 }, { 1, 4, 0.1 }, { 0,0,0.5,1 }));
				_letters.push_back(new SolidoRigido(gScene, gPhysics, { 47,-35,-85 }, { 5, 1, 0.1 }, { 0,0,0.5,1 }));
				break;
			case WIND1:
				//_letters.push_back(new SolidoRigido(gScene, gPhysics, { 40, 12, -100 }, { 5, 2, 5}, { 0,0,0.5,1 }));
				break;
			case WIND2:
				//_letters.push_back(new SolidoRigido(gScene, gPhysics, { -10, -40, -100 }, { 5, 3, 5}, { 0,0,0.5,1 }));
				break;

			case DEFAULT:break;
			case RESTARTGAME:break;
		
		default: break;
		}
	}
public:
	Button(PxScene* gS, PxPhysics* gP, physx::PxTransform pos, float width, float height, Functions f, LevelSystem* _level, Vector4 _color = { 0.8,0.8,0.8,1 }, float  length = 0.1):InteractuableObject(pos.p, height+2, width, 1){
		gScene = gS;
		gPhysics = gP;
		obj = new SolidoRigido(gS, gP, pos, { width, height, length }, _color);
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

