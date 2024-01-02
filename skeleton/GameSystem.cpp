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
	_levelManager->active = false;
	_buttonList.push_back(new Button(gScene, gPhysics, { 0,1,-80 }, 25, 10, Button::STARTGAME, _levelManager));

}

void GameSystem::LevelMenuInicialice() {
	_levelManager->active = false;
	endWin_text1 = " ";  endWin_text2 = " "; endWin_text3 = " ";
	endLoose_text1 = " "; endLoose_text2 = " "; continue_text = " ";
	instructions_1 = " "; instructions_2 = " "; instructions_3 = " "; instructions_4 = " "; instructions_5 = " "; instructions_6 = " "; instructions_7 = " ";
	_buttonList.push_back(new Button(gScene, gPhysics, { -50,15,-90 }, 10, 10, Button::LEVEL_1, _levelManager));
	_buttonList.push_back(new Button(gScene, gPhysics, { 0,15,-90 }, 10, 10, Button::LEVEL_2, _levelManager));
	_buttonList.push_back(new Button(gScene, gPhysics, { 50,15,-90 }, 10, 10, Button::LEVEL_3, _levelManager));
	_buttonList.push_back(new Button(gScene, gPhysics, { -50,-20,-90 }, 10, 10, Button::LEVEL_4, _levelManager));
	_buttonList.push_back(new Button(gScene, gPhysics, { 0,-20,-90 }, 10, 10, Button::LEVEL_5, _levelManager));
	_buttonList.push_back(new Button(gScene, gPhysics, { 50,-20,-90 }, 10, 10, Button::LEVEL_6, _levelManager));
	
}

void GameSystem::GameSceneInicialice() {
	_levelManager->active = true;
	_buttonList.push_back(new Button(gScene, gPhysics, { 83,45,-90 }, 4, 4, Button::BACK, _levelManager));
}

void GameSystem::Instructions() {
	instructions_1 = "NEST";
	instructions_2 = "HELP THE BIRD TO THE NEST"; 
	instructions_3 = "DO NOT LET IT TOUCH THE RED ENEMIES OR THE BIRD WILL DIE!"; 
	instructions_4 = "DO NOT LET IT FALL TO THE GROUND, IT DOES NOT KNOW HOW TO FLY YET!"; 
	instructions_5 = "CLICK THE OBSTACLES TO REMOVE THEM";
	instructions_6 = "CLICK THE ENEMIES TO CHANGE THEIR FORM";
	instructions_7 = "PRESS SPACE TO CHANGE THE BIRD'S FORM";

	_buttonList.push_back(new Button(gScene, gPhysics, { 0,-2,-80 }, 35, 12, Button::INSTRUCTIONS, _levelManager));
}

void GameSystem::EndSceneInicialice() {
	_levelManager->active = false;
	endWin_text3 = "Good luck :)";
	continue_text = "CONTINUE";
	if (win) {
		endWin_text1 = "You won!";
		endWin_text2 = "But the fun is not over, try the next level!";
	}
	else {
		endLoose_text1 = "You lost!";
		endLoose_text2 = "Don't give up yet, just try again!";
	}
	_buttonList.push_back(new Button(gScene, gPhysics, { 0,0,-80 }, 25, 10, Button::DEFAULT, _levelManager));
	_buttonList.push_back(new Button(gScene, gPhysics, { 0,-20,-75 }, 10, 2, Button::RESTARTGAME, _levelManager));

}

void GameSystem::ManageScene() {
	if (changeMenu) {
		switch (actualMenu)
		{
		case MAINMENU: MainMenuInicialice();
			break;
		case INSTRUCTIONS: Instructions();
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
	if (!_levelManager->active || (_levelManager->active && !_levelManager->endGame)) {
		for (auto it = _pointers.begin(); it != _pointers.end();) {
			bool alive = true;
			if ((*it)->isAlive()) {
				(*it)->integrate(t);
				for (auto ot = _buttonList.begin(); ot != _buttonList.end();) {
					if ((*ot)->function != Button::DEFAULT && (*ot)->insideBoundingBox((*it)->getPosition())) {
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

						if ((*ot)->insideBoundingBox((*it)->getPosition(), (*it)->_scale, (*ot)->getPosition())) {
							if ((*ot)->_type != "ENEMY" && (*ot)->_type != "ENEMYFLOOR") {
								delete(*ot);
								ot = _levelManager->_objPorNivel.erase(ot);
								delete(*it);
								it = _pointers.erase(it);
								alive = false;
							}
							else if ((*ot)->_type == "ENEMY") {
								_levelManager->changeFormEnemy((*ot));
								delete(*it);
								it = _pointers.erase(it);
								alive = false;
							}
							else ++ot;
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