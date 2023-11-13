#pragma once
#include <map>
#include "ForceGenerator.h"

typedef std::pair<ForceGenerator*, Particle*> FRPair;

class ParticleForceRegistry : public std::multimap<ForceGenerator*, Particle*> {
public:
	void updateForces(double duration) {
		for (auto it = begin(); it != end(); ++it) {
			it->first->updateForce(it->second, duration);
		}
	}

	void addRegistry(ForceGenerator* fg, Particle* p) {
		insert(FRPair(fg,p));
	}

	void deleteParticleRegistry(Particle* p) {
		for (auto it = begin(); it != end();) {
			if (it->second == p) erase(it);
			else ++it;
		}
	}
};
