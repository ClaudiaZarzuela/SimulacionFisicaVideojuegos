#pragma once
#include "Particle.h"
#include "ParticleGenerator.h"
#include "GaussianParticleGenerator.h"
#include "UniformParticleGenerator.h"
#include "FireworkGenerator.h"
#include <list>
#include "GravityForceGenerator.h"
#include "ParticleDragGenerator.h"
#include "ParticleForceRegistry.h"
#include "ParticleWhirlWindGenerator.h"
#include "SpringForceGenerator.h"
#include "ExplotionGenerator.h"
#include "AnchoredSpringFG.h"
#include "SpringForceGenerator.h"
#include "ElasticForceGenerator.h"
#include "BuoyancyForceGenerator.h"
#include <set>
#include "SolidoRigido.h"
#include "Nest.h"
#include "Button.h"
#include "Player.h"
#include "Decoration.h"
#include "Enemy.h"
#include "WindMill.h"

/*
Clase encargada de la creaci�n y del desarrollo de mec�nicas y funcionalidad de los niveles. En su constructora se inicializa el BoundingBox usado para la destrucci�n de 
cada entidad que lo sobrepase.

La creaci�n de cada nivel tiene un m�todo propio. En estos m�todos se crean todos los objetos del nivel (jugador, enemigos, nido (objetivo final), objetos
normales y ventiladores) y se a�aden a la lista _objPorNivel. Tambi�n se inicializan tanto las fuerzas (dragForce, whirldwind, gravity y bouyancy) como los 
generadores de entidades (gaussiano, uniforme y fireworks) que se usen por nivel, a�adiendolos al la lista _force_generators y posteriormente al registro 
ParticleForceRegistry para su integraci�n.

Una vez recibida la llamada del GameSystem especificando en que nivel estamos para llamar a su m�todo correspondiente comienza el bucle del juego (integrate).

Este bucle se encarga de (en orden):
	- mira si alguna fuerza es puntual y se le ha acabado el tiempo de vida para eliminarlo del registro
	- integra todas las fuerzas que se necesiten en ese nivel para que afecte a sus particulas asociadas correctamente
	- llama a los generadores de partriculas y a�ade las nuevas a la lista y a las fuerzas actuales
	- recorre la lista de particulas para integrarlas en caso de que esten vivas y dentro del bounding box. De lo contrario, checkea si 
	  generan m�s particulas al morir (firework) y las elimina de la lista y del registro de fuerzas

	Comprueba si el jugador no a muerto para:
		- checkea si ha colisionado con alg�n boton y llama a su funci�n (activar su ventilador asociado)
		- checkea si ha colisionado con alg�n enemigo. En caso de hacerlo, el jugador muere y para indicarlo, en su misma posici�n ,sale un firework rojo. 
		- si no ha muerto, checkea si ha entrado en el nido.  En caso de hacerlo, el jugador gana y para indicarlo,como antes, sale un firework verde. 

 Si ha muerto, tras pasar algunos segundos se cambia de escena al menu final, especifiacndo si ha perdido (se ha muerto por chocarse con un enemigo) 
 o ganado (a entrado en el nido)
*/

//Referencias externas de booleanos de cambio de escenas
extern bool changeMenu;
extern int actualMenu;
extern bool win;

class LevelSystem
{
private: 
	//BOUNDING BOX
	struct BoundingBox {
		int minX, maxX;
		int minY, maxY;
		int minZ, maxZ;
	};
	BoundingBox box;
	void inicialiceBoundingBox();
	bool insideBoundingBox(Vector3 pos);
	//---------------------------------------------------------------------------------------------

	int _timer = 3;
	double elapsedTime = 0;

	PxScene* gScene = nullptr;
	PxPhysics* gPhysics = nullptr;
	Vector3 _gravity;
	//---------------------------------------------------------------------------------------------

	Nest* _nest = nullptr; //referencia al nido
	Entity* _player = nullptr; //referencia al jugador
	bool explodePlayer = true; //booleano que indica si el jugador ha muerto
	//---------------------------------------------------------------------------------------------

	//Listas de entidades,decoraci�n, fuerzas y botones usados
	std::list<Entity*> _particles;
	std::list<Decoration*> _decor;
	std::list <ParticleGenerator*> _particle_generators;
	std::set<ForceGenerator*> _force_generators;
	FireworkGenerator* _firework_generator = nullptr;
	ParticleForceRegistry* _force_registry = nullptr;
	GravityForceGenerator* _gravityForce = nullptr;
	BuoyancyForceGenerator* _bouyancyForce = nullptr;
	std::list<Button*> _buttonList;
	//---------------------------------------------------------------------------------------------

	//Ventiladores
	WindMill* viento = nullptr;
	ParticleDragGenerator* wind1 = nullptr;
	ParticleDragGenerator* wind2 = nullptr;
	WindMill* viento2 = nullptr;
	bool activeWind1 = false;
	bool activeWind2 = false;
	//---------------------------------------------------------------------------------------------

	//A�ade entidades a fuerzas especificas
	void registerParticlesToForce(std::list<Entity*> p);
	void registerParticleToForce(Entity* p);
	void registerParticleToSpecificForce(Entity* p, ForceGenerator* f);
	//---------------------------------------------------------------------------------------------

	//M�todo llamado cuando el jugador muere. Se encarga de borrar al jugador y acttivar un booleano que se encagra de 
	//cambiar de pantalla a la de "FIN" si se ha acabado la partida. Tambien especifica si se ha perdido o ganado para 
	// generar los textos correspondientes.
	void playerDies(bool _win);

	//A�ade las fuerzas b�sicas al juego como la gravedad e inicializa el ParticleForceRegistry
	void addForces();

	//Elimina todos los objetos en pantalla tras terminar un nivel
	void reset();

	//Genera un lago con cubos de hielo (part�culas rectangulares) floatndo al fondo usando el BuoyancyForceGenerator. 
	void generateBouyancy();

	//Simula una tormenta de hielo usando varios generadores de part�culas uniformes con fuerzas de viento (ParticleDragGenerator) y 
	// trobellinos (ParticleWhirlWindGenerator)
	void iceStorm();

public:

	LevelSystem(PxScene* gS, PxPhysics* gP, const Vector3& g = { 0.0f, -10.0f, 0.0f });
	~LevelSystem();

	void keyPress(unsigned char key);
	void integrate(double t);
	//---------------------------------------------------------------------------------------------

	//Activa los ventiladores tras pulsar su bot�n asociado
	void activateWind1();
	void activateWind2();

	//Eliminia todos los objetos, incluso el jugador, cuando se hace click en el bot�n de BACK, el cu�l te lleva al men� de niveles.
	//Esto evita que el jugador se estre si se ha equivocado de nivel o si es incapaz de terminarlo.
	void back();

	//Cambia de forma al jugador y a los enemigos, de esfera a box y viceversa.
	void changeFormEnemy(Entity* obj);
	void changeFormPlayer();

	//Firework que aparece cuando el jugador muere (rojo si pierde y verde si gana)
	void shootFirework();

	//M�todos para la creaci�n de cada nivel
	void startLevel1();
	void startLevel2();
	void startLevel3();
	void startLevel4();
	void startLevel5();
	void startLevel6();
	//---------------------------------------------------------------------------------------------

	bool active = false;
	std::list<Entity*> _objPorNivel;
	bool endGame = false;
	bool level4 = false;
	bool level2 = false;
};

