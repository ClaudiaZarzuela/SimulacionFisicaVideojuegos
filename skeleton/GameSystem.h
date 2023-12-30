#pragma once
#include "Particle.h"
#include <list>
#include <string>
#include "Weapon.h"
#include "Button.h"
#include "LevelSystem.h"

static enum Menus {
	MAINMENU = 0, LEVELMENU = 1, GAMESCENE = 2, ENDSCENE = 3
};
using namespace physx;
extern bool changeMenu;
extern int actualMenu;
extern int levelIndex;
extern std::string endWin_text1;
extern std::string endWin_text2;
extern std::string endWin_text3;
extern  std::string endLoose_text1;
extern  std::string endLoose_text2;
extern  std::string continue_text;
extern bool win;
class GameSystem
{
private:
	//MAIN MENU
	void MainMenuInicialice();

	//LEVELS MENU
	void LevelMenuInicialice();
	LevelSystem* _levelManager = nullptr;
	//GAME SCENE
	void GameSceneInicialice();

	//END SCENE
	void EndSceneInicialice();

	//GAME STATE MACHINE
	void ManageScene();
	std::list<Button*> _buttonList;
	void clearButtons();
//------------------------------------------------------------------------------

	Weapon* _proyectil = nullptr;
	std::list<Entity*> _pointers;
	int _timer = 1;
	double elapsedTime = 0;
	bool activePointer = true;

	PxScene* gScene = nullptr;
	PxPhysics* gPhysics = nullptr;
	Vector3 _gravity;

	void showAvailableKeys();

public:
	void keyPress(unsigned char key);
	void integrate(double t);
	void handleMouse(int button, int state, int x, int y);
	GameSystem(PxScene* gS, PxPhysics* gP, const Vector3& g = { 0.0f, -10.0f, 0.0f });
	~GameSystem();
};



