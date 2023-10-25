#include "Firework.h"
#include <iostream>
Firework::Firework(Vector3 Pos, Vector3 Vel, Vector3 A, float Damping, float Masa, Vector3 Gravedad, float Time, Vector4 color, int numParticulas, int generacion, bool modelo, double scale):
Particle(Pos, Vel, A, Damping,Masa, Gravedad, Time, color, modelo, scale){
	type = FIREWORK;
	numP = numParticulas;
	generacionActual = generacion;
}

std::list<Particle*> Firework::explode(Firework* f) {
	f->_pose.p = this->_pose.p;
	ParticleGenerator* p = new FireworkParticleGenerator(f);
	std::list<Particle*> s = p->generateParticles();
	delete(p);
	return s;
}

Firework* Firework::clone() const {
	return new Firework(_pose.p, _vel, a, damping, masa, gravedad, maxTime, _color, numP, generacionActual, false, scale);
}
