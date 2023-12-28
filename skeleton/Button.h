#pragma once
#include "SolidoRigido.h"
#include "InteractuableObject.h"
class GameSystem;
class LevelSystem;
extern bool changeMenu;
extern int actualMenu;
extern int levelIndex;
class Button : public InteractuableObject
{
public:
	enum Functions {
		STARTGAME = 0, LEVEL_1 = 1, LEVEL_2 = 2, LEVEL_3 = 3, LEVEL_4 = 4
	};
private:
	SolidoRigido* button = nullptr;
	LevelSystem* _levelSystem = nullptr;
	Functions function;
	void startGame();
	void startLevel(int i);
public:
	Button(PxScene* gS, PxPhysics* gP, physx::PxTransform pos, float width, float height, Functions f, LevelSystem* _level):InteractuableObject(pos.p, height, width, 1){
		button = new SolidoRigido(gS, gP, pos, { width, height, 1 }, { 0.8,0.8,0.8,1 });
		function = f;
		_levelSystem = _level;
	}
	void startFunction() {
		switch (function) {
		case STARTGAME: startGame(); break;
			case LEVEL_1: startLevel(0); break;
			case LEVEL_2: startLevel(1); break;
			case LEVEL_3: startLevel(2); break;
			case LEVEL_4: startLevel(3); break;
			default: break;
		}
	}
	virtual ~Button() {
		if(button != nullptr) delete(button);
	}

	
};

