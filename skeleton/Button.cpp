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
	_levelSystem->startLevel1();
}
