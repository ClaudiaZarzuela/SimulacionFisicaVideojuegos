#pragma once
#include <string>
#include <PxPhysicsAPI.h>>
using namespace physx;
using namespace std;
/// Clase base que proporcionará funcionalidad a nuestros estados
class GameState {
protected:
    PxScene* gScene = nullptr;
    PxPhysics* gPhysics = nullptr;
    string stateID; // Identificador del estado
    GameState(string stateID, PxScene* gS, PxPhysics* gP) : stateID(stateID), gScene(gS), gPhysics(gP){}
    //Creamos un manager nuevo para cada estado e interrumpimos la lectura de teclado

public:
    virtual ~GameState() {} 
    virtual void update() {}
    virtual void render() const { }
    virtual void refresh() {  }
    virtual void keyPressed(int key) {  }
    virtual void keyReleased(int key) {  }
    virtual string getStateID() const { return stateID; };
};