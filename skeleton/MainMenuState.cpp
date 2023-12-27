#include "MainMenuState.h"

MainMenuState::MainMenuState(string name, PxScene* gS, PxPhysics* gP): GameState(name, gS, gP), stateID(name){
	title_text = "Lolazo";
	_startButton = new Button(gS, gP,{0,0,-700},125,50);
}