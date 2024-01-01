#include "Button.h"
#include "GameSystem.h"
#include "LevelSystem.h"
void Button::startGame() {
	actualMenu = Menus::LEVELMENU;
	changeMenu = true;
}
void Button::instructions() {
	actualMenu = Menus::INSTRUCTIONS;
	changeMenu = true;
}
void Button::startLevel(int i) {
	actualMenu = Menus::GAMESCENE;
	changeMenu = true;
	levelIndex = i;
	switch (i) {
		case 0: _levelSystem->startLevel1(); break;
		case 1: _levelSystem->startLevel2(); break;
		case 2: _levelSystem->startLevel3(); break;
		case 3: _levelSystem->startLevel4(); break;
		case 4: _levelSystem->startLevel5(); break;
		case 5: _levelSystem->startLevel6(); break;
		case 6: _levelSystem->startLevel7(); break;
		case 7: _levelSystem->startLevel8(); break;
		default: break;
	}
}
void  Button::startFunction() {
	switch (function) {
	case STARTGAME:instructions(); break;
	case INSTRUCTIONS: startGame(); break;
	case BACK: _levelSystem->back(); startGame(); break;
	case RESTARTGAME: startGame(); break;
	case LEVEL_1: startLevel(0); break;
	case LEVEL_2: startLevel(1); break;
	case LEVEL_3: startLevel(2); break;
	case LEVEL_4: startLevel(3); break;
	case DEFAULT:break;
	default: break;
	}
}
