#pragma once
#include "Particle.h"
#include <list>
#include <string>
#include "Weapon.h"
#include "Button.h"
#include "LevelSystem.h"

/*
	Clase principal encargada de la gesti�n de menus asi como de la creaci�n de los "pointers": balas de proyectil (part�culas) sin graverdad creadas en la posici�n del rat�n
	en pantalla con una velocidad de (0,0,-z) que simulan el click del rat�n.

	Inicializa los textos correspondientes que salen en pantalla: las instruccion, el nombre, pantalla de fin dependiendo de si se ha ganado o perdido y comentarios sobre 
	una funcionalidad espec�fica de algunos niveles.

	Cada men�/pantalla de juego tiene su propio m�todo donde se crear�n los objetos de decoraci�n y botones adecuados.

	En la constructora se crea y guarda la referencia del LevelSystes, el cual se encarga de toda la funcionalidad de los niveles en s�. Por tanto, tras detectar ccolision entre alg�n pointer
	con alg�n boton de nivel, este llama al m�todo del nivel seleccionado del levelSystem para que comience la partida.

	Cada vez que se cambia de escena, los objetos creados y guardados en _buttonList (botones), _decorationIntro (decoraci�n), _pointers (punteros) se eliminan completamente para poder empezar
	una nueva pantalla desde cero con objetos nuevos.

	Por �ltimo, el GameSystem tambi�n se encarga de borrar un pointer si se le ha acabado el tiempo de vida. No es necesario un BoundingBox ya que los ponters van muy r�pido y tienen muy poca vida,
	a parte de que solo puede salir 1 pointer cada segundo por lo que no se generan tantos en pantalla a la vez.
*/

//Enumerado con los menus/escenas de juego
static enum Menus {
	MAINMENU = 0, LEVELMENU = 1, GAMESCENE = 2, ENDSCENE = 3, INSTRUCTIONS = 4
};

//Referencias a los textos de la clase Render para poder mostrarlos correctamente a su tiempo
using namespace physx;
extern bool changeMenu;
extern int actualMenu;
extern int levelIndex;
extern std::string  name_text;
extern std::string endWin_text1;
extern std::string endWin_text2;
extern std::string endWin_text3;
extern std::string endLoose_text1;
extern std::string endLoose_text2;
extern std::string continue_text;
extern std::string instructions_1;
extern std::string instructions_2;
extern std::string instructions_3;
extern std::string instructions_4;
extern std::string instructions_5;
extern std::string instructions_6;
extern std::string instructions_7;

extern bool win;
class GameSystem
{
private:
	//MAIN MENU
	void MainMenuInicialice();

	//LEVELS MENU
	void LevelMenuInicialice();
	LevelSystem* _levelManager = nullptr;
	//GAME SCENE
	void GameSceneInicialice();

	//INSTRUCTIONS
	void Instructions();

	//END SCENE
	void EndSceneInicialice();

	//GAME STATE MACHINE
	void ManageScene();
	std::list<Button*> _buttonList;
	void clearButtons();
//------------------------------------------------------------------------------

	Weapon* _proyectil = nullptr;
	std::list<Entity*> _pointers;
	std::list<Entity*> _decorationIntro;
	int _timer = 1;
	double elapsedTime = 0;
	bool activePointer = true;
	PxScene* gScene = nullptr;
	PxPhysics* gPhysics = nullptr;
	Vector3 _gravity;

public:
	void keyPress(unsigned char key);
	void integrate(double t);
	void handleMouse(int button, int state, int x, int y);
	GameSystem(PxScene* gS, PxPhysics* gP, const Vector3& g = { 0.0f, -10.0f, 0.0f });
	~GameSystem();
};



