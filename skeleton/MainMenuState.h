#pragma once
#include "GameState.h"
#include "RenderUtils.hpp"
#include "Button.h"

extern std::string title_text;
class MainMenuState : public GameState
{
private:
	Button* _startButton;
public:
	std::string stateID;

	MainMenuState(string name, PxScene* gS, PxPhysics* gP);
	virtual ~MainMenuState() {}
	void render() const override {};
	void update() override {};
	void keyPressed(int key) override {};
};