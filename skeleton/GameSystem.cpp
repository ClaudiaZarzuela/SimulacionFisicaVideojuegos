#include "GameSystem.h"
#include <iostream>

GameSystem::GameSystem(PxScene* gS, PxPhysics* gP, const Vector3& g) {
	gPhysics = gP;
	gScene = gS;
	_gravity = g;

	//Activate proyectil, used as a cursor
	_proyectil = new Weapon(Weapon::Types::LASER);
	showAvailableKeys();
	inicialiceBoundingBox();
	actualMenu = MAINMENU;
	_levelManager = new LevelSystem(gScene, gPhysics);
}

void GameSystem::showAvailableKeys() {
	std::cout << "CONTROLS:" << std::endl;
	std::cout << "- blah blah blah blah" << std::endl;
	std::cout << "--------------------------------------------------------" << std::endl;
}

void GameSystem::MainMenuInicialice() {
	std::cout << "MAIN MENU" << std::endl;
	title_text = "NEST";
	_buttonList.push_back(new Button(gScene, gPhysics, { 0,0,-100 }, 25, 10, Button::STARTGAME));

}

void GameSystem::LevelMenuInicialice() {
	std::cout << "LEVELS MENU" << std::endl;
	title_text = "LEVELS MENU";
	_buttonList.push_back(new Button(gScene, gPhysics, { -75,15,-100 }, 10, 10, Button::LEVEL_1));
	_buttonList.push_back(new Button(gScene, gPhysics, { 25,15,-100 }, 10, 10, Button::LEVEL_2));
	_buttonList.push_back(new Button(gScene, gPhysics, { -25,15,-100 }, 10, 10, Button::LEVEL_1));
	_buttonList.push_back(new Button(gScene, gPhysics, { 75,15,-100 }, 10, 10, Button::LEVEL_2));

	_buttonList.push_back(new Button(gScene, gPhysics, { -75,-20,-100 }, 10, 10, Button::LEVEL_3));
	_buttonList.push_back(new Button(gScene, gPhysics, { 25,-20,-100 }, 10, 10, Button::LEVEL_4));
	_buttonList.push_back(new Button(gScene, gPhysics, { 75,-20,-100 }, 10, 10, Button::LEVEL_3));
	_buttonList.push_back(new Button(gScene, gPhysics, { -25,-20,-100 }, 10, 10, Button::LEVEL_4));
	
}

void GameSystem::GameSceneInicialice() {
	std::cout << "GAME SCENE" << std::endl;
	title_text = " ";
}

void GameSystem::EndSceneInicialice() {
	std::cout << "END MENU" << std::endl;
}

void GameSystem::ManageScene() {
	if (changeMenu) {
		switch (actualMenu)
		{
		case MAINMENU: MainMenuInicialice();
			break;
		case LEVELMENU:LevelMenuInicialice();
			break;
		case GAMESCENE:GameSceneInicialice();
			break;
		case ENDSCENE:EndSceneInicialice();
			break;
		default:
			break;
		}
		changeMenu = false;
	}
}

void GameSystem::integrate(double t) {
	ManageScene();

	for (auto it = _pointers.begin(); it != _pointers.end();) {
		if ((*it)->isAlive() && insideBoundingBox((*it)->getPosition())) {
			(*it)->integrate(t);
			for (auto ot = _buttonList.begin(); ot != _buttonList.end();) {
				if ((*ot)->insideBoundingBox((*it)->getPosition())) {
					(*ot)->startFunction();
					clearButtons();
					ot = _buttonList.end();
				}
				else ++ot;
			}
			++it;
		}
		else {
			delete(*it);
			it = _pointers.erase(it);
		}

	}
}

bool GameSystem::insideBoundingBox(Vector3 pos) {
	return (pos.x > box.minX && pos.x <= box.maxX) && (pos.y >= box.minY && pos.y <= box.maxY) && (pos.z > box.minZ && pos.z <= box.maxZ);
}

void GameSystem::keyPress(unsigned char key) {
	switch (toupper(key))
	{
		default:break;
	}
	
}

void GameSystem::handleMouse(int button, int state, int x, int y)
{
	if (button == 0) {
		Vector3 mousePos = { GetCamera()->getMousePos().x,GetCamera()->getMousePos().y, 0 };
		_pointers.push_back(_proyectil->shoot({ mousePos.x/5,mousePos.y/5,-1 }, {0,0,0}));
	}
}

void GameSystem::inicialiceBoundingBox() {
	box = { -1000, 1000, -10, 1000, -1000, 1000 };
}

void GameSystem::clearButtons() {
	for (auto it = _buttonList.begin(); it != _buttonList.end();) {
		delete(*it);
		it = _buttonList.erase(it);
	}
}

GameSystem::~GameSystem() {
	for (auto it = _pointers.begin(); it != _pointers.end();) {
		delete(*it);
		it = _pointers.erase(it);
	}
	clearButtons();
	delete(_proyectil);
	delete(_levelManager);
}