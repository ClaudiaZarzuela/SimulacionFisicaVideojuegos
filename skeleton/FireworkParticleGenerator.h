#pragma once
#include "GaussianParticleGenerator.h"
class Firework;
class FireworkParticleGenerator : public GaussianParticleGenerator
{
public:
	FireworkParticleGenerator(Firework* modelo);
	virtual std::list<Particle*> generateParticles() override;
private:
	Firework* modelo = nullptr;
};

