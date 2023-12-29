#include "Button.h"
#include "GameSystem.h"
#include "LevelSystem.h"
void Button::startGame() {
	actualMenu = Menus::LEVELMENU;
	changeMenu = true;
}
void Button::startLevel(int i) {
	actualMenu = Menus::GAMESCENE;
	changeMenu = true;
	levelIndex = i;
	switch (i) {
		case 0: _levelSystem->startLevel1(); break;
		case 1: _levelSystem->startLevel2(); break;
		default: break;
	}
}
