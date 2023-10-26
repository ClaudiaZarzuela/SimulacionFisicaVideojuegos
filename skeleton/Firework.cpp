#include "Firework.h"
#include <iostream>
#include "FireworkGenerator.h"
Firework::Firework(Vector3 Pos, Vector3 Vel, Vector3 A, float Damping, float Masa, Vector3 Gravedad, float Time, Vector4 color, int numParticulas, int generacion, FireworkGenerator* originalGenerator, bool modelo, double scale):
Particle(Pos, Vel, A, Damping,Masa, Gravedad, Time, color, modelo, scale){
	numP = numParticulas;
	generacionActual = generacion;
	_gen = originalGenerator;
}

std::list<Particle*> Firework::explode() {
	Firework* model = _gen->getModel(generacionActual + 1);
	model->_pose.p = this->_pose.p;
	GaussianParticleGenerator* pGen = new GaussianParticleGenerator(Vector3(0.1, 0.1, 0.1), model->_pose.p, Vector3(8, 8, 8), model->_vel, model->numP);
	pGen->setParticle(model);
	std::list<Particle*> s = pGen->generateParticles();
	delete(pGen);
	return s;
}

Particle* Firework::clone() const {
	return new Firework(_pose.p, _vel, a, damping, masa, gravedad, maxTime, _color, numP, generacionActual, _gen, false, scale);
}