#include "GameSystem.h"
#include <iostream>

GameSystem::GameSystem(PxScene* gS, PxPhysics* gP, const Vector3& g) {
	gPhysics = gP;
	gScene = gS;
	_gravity = g;

	//Activate proyectil, used as a cursor
	_proyectil = new Weapon(Weapon::Types::LASER);
	showAvailableKeys();
	actualMenu = MAINMENU;
	_levelManager = new LevelSystem(gScene, gPhysics);
	_levelManager->active = false;
}

void GameSystem::showAvailableKeys() {
	std::cout << "CONTROLS:" << std::endl;
	std::cout << "- blah blah blah blah" << std::endl;
	std::cout << "--------------------------------------------------------" << std::endl;
}

void GameSystem::MainMenuInicialice() {
	std::cout << "MAIN MENU" << std::endl;
	title_text = "NEST";
	_buttonList.push_back(new Button(gScene, gPhysics, { 0,0,-80 }, 25, 10, Button::STARTGAME, _levelManager));

}

void GameSystem::LevelMenuInicialice() {
	std::cout << "LEVELS MENU" << std::endl;
	title_text = "LEVELS MENU";
	_buttonList.push_back(new Button(gScene, gPhysics, { -65,15,-90 }, 10, 10, Button::LEVEL_1, _levelManager));
	_buttonList.push_back(new Button(gScene, gPhysics, { -20,15,-90 }, 10, 10, Button::LEVEL_2, _levelManager));
	_buttonList.push_back(new Button(gScene, gPhysics, { 20,15,-90 }, 10, 10, Button::LEVEL_3, _levelManager));
	_buttonList.push_back(new Button(gScene, gPhysics, { 65,15,-90 }, 10, 10, Button::LEVEL_4, _levelManager));
	_buttonList.push_back(new Button(gScene, gPhysics, { -65,-20,-90 }, 10, 10, Button::LEVEL_5, _levelManager));
	_buttonList.push_back(new Button(gScene, gPhysics, { -20,-20,-90 }, 10, 10, Button::LEVEL_6, _levelManager));
	//SolidoRigido* num_7_top = new SolidoRigido(gScene, gPhysics, { 19,-13,-85 }, { 5, 1, 0.1 }, {1,0,1,1}); //cambiar a este color cuando pulsas un boton
	_buttonList.push_back(new Button(gScene, gPhysics, { 20,-20,-90 }, 10, 10, Button::LEVEL_7, _levelManager));
	_buttonList.push_back(new Button(gScene, gPhysics, { 65,-20,-90 }, 10, 10, Button::LEVEL_8, _levelManager));
	
}

void GameSystem::GameSceneInicialice() {
	std::cout << "GAME SCENE" << std::endl;
	title_text = " ";
	_levelManager->active = true;
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
	if (!activePointer) {
		elapsedTime += t;
		if (elapsedTime >= _timer) activePointer = true;
	}
	ManageScene();

	_levelManager->integrate(t);
	for (auto it = _pointers.begin(); it != _pointers.end();) {
		bool alive = true;
		if ((*it)->isAlive()) {
			(*it)->integrate(t);
			for (auto ot = _buttonList.begin(); ot != _buttonList.end();) {
				if ((*ot)->insideBoundingBox((*it)->getPosition())) {
					(*ot)->onButtonClicked();
					(*ot)->startFunction();
					clearButtons();
					ot = _buttonList.end();
					delete(*it);
					it = _pointers.erase(it);
					alive = false;
				}
				else ++ot;
				
			}
			if (_levelManager->active) {
				auto ot = _levelManager->_objPorNivel.begin();
				while(alive && ot != _levelManager->_objPorNivel.end()){

					if ((*ot)->insideBoundingBox((*it)->getPosition())) {
						delete(*ot);
						ot = _levelManager->_objPorNivel.erase(ot);
						delete(*it);
						it = _pointers.erase(it);
						alive = false;
					}
					else ++ot;
				}
			}
			if(alive)++it;
		}
		else {
			delete(*it);
			it = _pointers.erase(it);
		}

	}
	
	
}

void GameSystem::keyPress(unsigned char key) {
	_levelManager->keyPress(key);
	switch (toupper(key))
	{
		default:break;
	}
	
}

void GameSystem::handleMouse(int button, int state, int x, int y)
{
	if (button == 0 && activePointer) {
		Vector3 mousePos = { GetCamera()->getMousePos().x,GetCamera()->getMousePos().y, 0 };
		_pointers.push_back(_proyectil->shoot({ mousePos.x/5,mousePos.y/5,-1 }, {0,0,0}));
		activePointer = false;
		elapsedTime = 0;
	}
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