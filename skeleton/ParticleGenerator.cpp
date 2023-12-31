#include "ParticleGenerator.h"
#include "Particle.h"
#include "SolidoRigido.h"

ParticleGenerator::ParticleGenerator(PxScene* gS, PxPhysics* gP):gScene(gS), gPhysics(gP) {
	_model_particle = new Particle(Vector3(0, 0, 0), Vector3(0, 10, 0), 0.3, 1.0f, 20.0f, true, { 0.7,0.7,1,0 },{0.3,0.3,0.3});
	if(gS != nullptr)_model_rigidbody = new SolidoRigido(gScene, gPhysics, {0,0,0}, {0,0,0}, {0,0,0}, {1,1,1},2,2, {0.8,0.8,0.8,1}, 30.0, "BOX","NORMAL",true);
};

void ParticleGenerator::setParticle(Particle* p) {
	if(_model_particle != nullptr) delete _model_particle;
	_model_particle = p;
}