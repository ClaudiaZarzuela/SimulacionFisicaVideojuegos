#include "AnchoredSpringFG.h"
AnchoredSpringFG::AnchoredSpringFG(double k, double resting, const Vector3& anchor_pos): SpringForceGenerator(k,resting, nullptr) {
	_other = new Particle(anchor_pos, { 0,0,0 }, 0, 1e6, Particle::BOX);
}
AnchoredSpringFG::~AnchoredSpringFG() {
	delete _other;
}