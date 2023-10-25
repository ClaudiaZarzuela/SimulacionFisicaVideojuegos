#pragma once
#include "Particle.h"
#include <list>
#include "FireworkParticleGenerator.h"
class Firework : public Particle
{
public:
	Firework(Vector3 Pos, Vector3 Vel, Vector3 A, float Damping, float Masa, Vector3 Gravedad, float Time, Vector4 color,
		int numParticulas, int generacion, bool modelo = false, double scale = 0.5);
	~Firework(){};
	// The firework generates more fireworks when exploding --> they should be gathered by the System
	std::list<Particle*> explode(Firework* f);
	//void addGenerator(ParticleGenerator* p);
	virtual Firework* clone() const;
	int getGenerations() { return generacionActual; }
	int getNumParticles() { return numP; }
protected:
	int numP;
	int generacionActual;

	
};