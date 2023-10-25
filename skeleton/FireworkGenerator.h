#pragma once
#include "Firework.h"
class FireworkGenerator
{
protected:
	int numGeneraciones;
	Firework* firework = nullptr;
public:

	Firework* shoot();
	FireworkGenerator(Firework* modelo, int numGen);
	~FireworkGenerator(){ delete firework; }
};

