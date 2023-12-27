#pragma once
#include "GameStateMachine.h"

GameState* GameStateMachine::currentState() const {
    return stateStack.front();
}

void GameStateMachine::pushState(GameState* state) {
    stateStack.push_front(state);
}

void GameStateMachine::changeState(GameState* state) {
    if (!stateStack.empty()) {
        if (stateStack.front()->getStateID() == state->getStateID()) return; //Si el estado que queremos sustituir es el mismo, no hacemos nada
        delete stateStack.front();
        stateStack.pop_front();
    }
    stateStack.push_front(state);
}

void GameStateMachine::popState() {
    if (!stateStack.empty()) {
        delete stateStack.front();
        stateStack.pop_front();
    }
}

void GameStateMachine::emptyStack() {
    while (!empty()) popState();
}

bool GameStateMachine::empty() {
    return stateStack.empty();
}

GameState* GameStateMachine::pop() {
    GameState* top = stateStack.front();
    stateStack.pop_front();
    return top;
}

void GameStateMachine::renderAllStates() {
    //Recorremos toda la pila de abajo a arriba para renderizar todos los estados al mismo tiempo
    auto it = stateStack.end();
    it--;

    for (; it >= stateStack.begin();) {
        (*it)->render();
        if (it > stateStack.begin()) --it;
        else break;
    }
}

void GameStateMachine::refreshAllStates() {
    //Recorremos toda la pila de abajo a arriba para refrescar todos los estados al mismo tiempo
    auto it = stateStack.end();
    it--;

    for (; it >= stateStack.begin();) {
        (*it)->refresh();
        if (it > stateStack.begin()) --it;
        else break;
    }
}