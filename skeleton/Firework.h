#pragma once
#include "Particle.h"
#include "GaussianParticleGenerator.h"
#include <list>

class Firework : public Particle
{
public:
	Firework(Vector3 Pos, Vector3 Vel, Vector3 A, float Damping, float Masa, Vector3 Gravedad, float Time, Vector4 color,
		int numParticulas, int generacion, FireworkGenerator* originalGenerator, bool modelo = false, Vector3 scale = { 0.5,0.5,0.5 });
	~Firework(){};
	// The firework generates more fireworks when exploding --> they should be gathered by the System
	virtual std::list<Entity*> explode();
	//void addGenerator(ParticleGenerator* p);
	virtual Particle* clone() const;
	int getGenerations() { return generacionActual; }
	int getNumParticles() { return numP; }

protected:
	int numP;
	int generacionActual;
	
};