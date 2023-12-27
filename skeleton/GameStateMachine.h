#pragma once
#include <deque>
#include "GameState.h"
using namespace std;
class GameStateMachine
{

public:
    deque<GameState*>  stateStack;
    GameStateMachine() = default;
    virtual ~GameStateMachine() { emptyStack(); };
    GameState* currentState() const;
    void pushState(GameState* state);
    void changeState(GameState* state);
    GameState* getPlayState() const { return stateStack.back(); }
    void popState();
    bool empty();
    void emptyStack();
    void renderAllStates();
    void refreshAllStates();
    GameState* pop();
};
