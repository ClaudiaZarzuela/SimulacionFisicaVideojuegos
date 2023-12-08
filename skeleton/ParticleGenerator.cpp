#include "ParticleGenerator.h"
#include "Particle.h"
#include "SolidoRigido.h"

ParticleGenerator::ParticleGenerator(PxScene* gS, PxPhysics* gP):gScene(gS), gPhysics(gP) {
	_model_particle = new Particle(Vector3(0, 0, 0), Vector3(0, 10, 0), 0.998, 1.0f, 20.0f, true);
	_model_rigidbody = new SolidoRigido(gScene, gPhysics, { 0,0,0 }, { 0,0,0 }, { 0,0,0 }, { 5,5,5 }, 0.15, { 0.8,0.8,0.8,1 },true);
};

void ParticleGenerator::setParticle(Particle* p) {
	if(_model_particle != nullptr) delete _model_particle;
	_model_particle = p;
}