#include "GameSystem.h"
#include <iostream>

GameSystem::GameSystem(PxScene* gS, PxPhysics* gP, const Vector3& g) {
	gPhysics = gP;
	gScene = gS;
	_gravity = g;

	//Activate proyectil, used as a cursor
	_proyectil = new Weapon(Weapon::Types::LASER);
	actualMenu = MAINMENU;
	_levelManager = new LevelSystem(gScene, gPhysics);
	_levelManager->active = false;
}

void GameSystem::MainMenuInicialice() {
	_levelManager->active = false;
	float floorWidth = 15;
	float floorLength = 5;
	float floorHeight = 1;
	float wallsHeight = 2;
	float wallsWidth = 1;

	physx::PxTransform pos = { 40,-40,-80 };
	_decorationIntro.push_back(new SolidoRigido(gScene, gPhysics, pos, { floorWidth, floorHeight, floorLength }, { 0.5,1,0.5,1 }));
	_decorationIntro.push_back(new Player(gScene, gPhysics, { 40,-36,-80 }, { 3,3,3 }, 100, 100));
	_decorationIntro.push_back(new SolidoRigido(gScene, gPhysics, pos, { floorWidth, floorHeight, floorLength }, { 0.5,1,0.5,1 }));
	physx::PxTransform posRight = { pos.p.x + floorWidth - wallsWidth, pos.p.y + floorHeight + wallsHeight , pos.p.z };
	physx::PxTransform posLeft = { pos.p.x - floorWidth + wallsWidth, pos.p.y + floorHeight + wallsHeight , pos.p.z };
	_decorationIntro.push_back(new SolidoRigido(gScene, gPhysics, posRight, { wallsWidth, wallsHeight, floorLength }, { 0.5,1,0.5,1 }));
	_decorationIntro.push_back(new SolidoRigido(gScene, gPhysics, posLeft, { wallsWidth, wallsHeight, floorLength }, { 0.5,1,0.5,1 }));
	_decorationIntro.push_back(new SolidoRigido(gScene, gPhysics, { 35,-32,-70 }, { 0.4,0.1,0.2 }, { 0,0,0,1 }));
	_decorationIntro.push_back(new SolidoRigido(gScene, gPhysics, { 38,-32,-70 }, { 0.4,0.1,0.2 }, { 0,0,0,1 }));
	_decorationIntro.push_back(new SolidoRigido(gScene, gPhysics, { 36.5,-34,-70 }, { 0.6,0.1,0.2 }, { 1, 0, 0, 1 }));
	_buttonList.push_back(new Button(gScene, gPhysics, { -1,2,-160 }, 47, 20, Button::STARTGAME, _levelManager));
	_decorationIntro.push_back(new Enemy(gScene, gPhysics, { 0,-45,-80 }, { 200, 0.1, 100 }));
	_decorationIntro.push_back(new Decoration(gScene, gPhysics, { -100,-25,-150 }, { 0.3,1,0.3 }, Decoration::TREE1));
	_decorationIntro.push_back(new Decoration(gScene, gPhysics, { 125,-15,-150 }, { 0.3,1.5,0.3 }, Decoration::TREE1));
	_decorationIntro.push_back(new Decoration(gScene, gPhysics, { 75,-25,-150 }, { 0.3,1,0.3 }, Decoration::TREE1));
	_decorationIntro.push_back(new Decoration(gScene, gPhysics, { -70,-20,-150 }, { 0.4,1,0.4 }, Decoration::TREE2));
	_decorationIntro.push_back(new Decoration(gScene, gPhysics, { -125,-20,-150 }, { 0.4,1,0.4 }, Decoration::TREE2));
	_decorationIntro.push_back(new Decoration(gScene, gPhysics, { -50,-40,-100 }, { 0.7,1.4,0.7 }, Decoration::SNOWMAN));
}

void GameSystem::LevelMenuInicialice() {
	
	_levelManager->active = false;
	endWin_text1 = " ";  endWin_text2 = " "; endWin_text3 = " ";
	endLoose_text1 = " "; endLoose_text2 = " "; continue_text = " ";
	instructions_1 = " "; instructions_2 = " "; instructions_3 = " "; instructions_4 = " "; instructions_5 = " "; instructions_6 = " "; instructions_7 = " ";
	_buttonList.push_back(new Button(gScene, gPhysics, { -50,5,-90 }, 10, 10, Button::LEVEL_1, _levelManager));
	_buttonList.push_back(new Button(gScene, gPhysics, { 0,5,-90 }, 10, 10, Button::LEVEL_2, _levelManager));
	_buttonList.push_back(new Button(gScene, gPhysics, { 50,5,-90 }, 10, 10, Button::LEVEL_3, _levelManager));
	_buttonList.push_back(new Button(gScene, gPhysics, { -50,-30,-90 }, 10, 10, Button::LEVEL_4, _levelManager));
	_buttonList.push_back(new Button(gScene, gPhysics, { 0,-30,-90 }, 10, 10, Button::LEVEL_5, _levelManager));
	_buttonList.push_back(new Button(gScene, gPhysics, { 50,-30,-90 }, 10, 10, Button::LEVEL_6, _levelManager));
	
}

void GameSystem::GameSceneInicialice() {
	_levelManager->active = true;
	_buttonList.push_back(new Button(gScene, gPhysics, { 83,45,-90 }, 4, 4, Button::BACK, _levelManager));
}

void GameSystem::Instructions() {
	for (auto it = _decorationIntro.begin(); it != _decorationIntro.end();) {
		delete(*it);
		it = _decorationIntro.erase(it);
	}
	instructions_1 = "NEST";
	instructions_2 = "HELP THE BIRD TO THE NEST"; 
	instructions_3 = "DO NOT LET IT TOUCH THE RED ENEMIES OR THE BIRD WILL DIE!"; 
	instructions_4 = "DO NOT LET IT FALL TO THE GROUND, IT DOES NOT KNOW HOW TO FLY YET!"; 
	instructions_5 = "CLICK THE OBSTACLES TO REMOVE THEM";
	instructions_6 = "CLICK THE ENEMIES TO CHANGE THEIR FORM";
	instructions_7 = "PRESS SPACE TO CHANGE THE BIRD'S FORM";

	_buttonList.push_back(new Button(gScene, gPhysics, { 0,-2,-80 }, 60, 12, Button::INSTRUCTIONS, _levelManager));
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
	//Para que no salgan varios pointers a la vez, sino que tengas que esperar 1 segundo entre clicks de ratón
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
				//Checkea si ha colisionado con un botón y, en caso de hacerlo, llama a su función, borra el pointer y los botones
				for (auto ot = _buttonList.begin(); ot != _buttonList.end();) {
					if ((*ot)->function != Button::DEFAULT && (*ot)->insideBoundingBox((*it)->getPosition())) {
						(*ot)->startFunction();
						if ((*ot)->function == Button::LEVEL_4 || (*ot)->function == Button::LEVEL_2) name_text = "THE BIRD CAN´T CHANGE FORM IN THIS LEVEL";
						else name_text = "Claudia Zarzuela Amor";
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
						//Checkea si ha colisionado con un objeto de nivel.
						//En caso de ser un enemigo, llama al LevelSytem para que lo cambie de forma y borra el pointer.
						//En caso de ser un objeto normal, lo borra de la lista y borra el pointer.
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

//Con la posición de la cámara, la cual te indica donde esta el ratón en pantalla, disparas un nuevo pointer usando el proyectil
void GameSystem::handleMouse(int button, int state, int x, int y)
{
	if (button == 0 && activePointer) {
		Vector3 mousePos = { GetCamera()->getMousePos().x,GetCamera()->getMousePos().y, 0 };
		_pointers.push_back(_proyectil->shoot({ mousePos.x/5,mousePos.y/5,-1 }, {0,0,0}));
		activePointer = false;
		elapsedTime = 0;
	}
}

//Elimina todos los botones en pantalla
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