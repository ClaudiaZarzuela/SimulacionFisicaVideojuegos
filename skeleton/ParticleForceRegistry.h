#pragma once
#include <map>
#include "ForceGenerator.h"
#include <unordered_set>

typedef std::pair<ForceGenerator*, Particle*> FRPair;

class ParticleForceRegistry : public std::multimap<ForceGenerator*, Particle*> {
public:
	void updateForces(double duration) {
		for (auto it = begin(); it != end(); ++it) {
			if (it->second->isAlive()) it->first->updateForce(it->second, duration);
		}

	}
	void addRegistry(ForceGenerator* fg, Particle* p) {
		insert(FRPair(fg, p));
	}
	void addRegistryToParticles(ForceGenerator* fg, std::list<Particle*> p) {
		for (auto it = p.begin(); it != p.end(); ++it) {
			addRegistry(fg, *it);
		}
	}

	void deleteParticleRegistry(Particle* p) {
		for (auto it = begin(); it != end();) {
			auto ot = it++;
			if (ot->second == p)
				erase(ot);
		}
	}
};