#include "FireworkGenerator.h"
FireworkGenerator::FireworkGenerator(Firework* modelo, int numGen) {
	firework = modelo;
	numGeneraciones = numGen;
}

Firework* FireworkGenerator::shoot() {
	return firework->clone();
}