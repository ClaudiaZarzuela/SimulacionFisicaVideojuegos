#include <ctype.h>
#include <PxPhysicsAPI.h>
#include <vector>
#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include <iostream>
#include "GameSystem.h"
#include "PxSceneDesc.h"


using namespace physx;

PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

GameSystem* _gameSystem = NULL;
std::string name_text = "Claudia Zarzuela Amor";
std::string endWin_text1 = " ";
std::string instructions = " ";
std::string endWin_text2 = " ";
std::string endWin_text3 = " ";
std::string endLoose_text1 = " ";
std::string endLoose_text2 = " ";
std::string continue_text = " ";
std::string instructions_1 = " ";
std::string instructions_2 = " ";
std::string instructions_3 = " ";
std::string instructions_4 = " ";
std::string instructions_5 = " ";
std::string instructions_6 = " ";
std::string instructions_7 = " ";
int WidthCam;
int HeightCam;
int actualMenu;
int levelIndex;
float gravity = -10.0f;
bool changeMenu = true;
bool win = true;

void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	sceneDesc.flags = PxSceneFlags(PxSceneFlag::eENABLE_STABILIZATION);

	gScene = gPhysics->createScene(sceneDesc);

	_gameSystem = new GameSystem(gScene, gPhysics);
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2) {
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}
// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);

	gScene->simulate(1.0f/120.0f);
	gScene->fetchResults(true);
	
	_gameSystem->integrate(t);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);
	delete(_gameSystem);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	
	gFoundation->release();

	}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	_gameSystem->keyPress(key);
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	default:
		break;
	}
}

void handleMouseInput(int button, int state, int x, int y)
{
	_gameSystem->handleMouse(button, state,x,y);
	PX_UNUSED(state);
	PX_UNUSED(button);
	
}
int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}