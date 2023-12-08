#pragma once
#include <map>
#include "ForceGenerator.h"
#include <unordered_set>
#include <iostream>


typedef std::pair<Entity*, ForceGenerator*> FRPair;

class ParticleForceRegistry : public std::multimap<Entity*, ForceGenerator*> {
public:
	void updateForces(double duration) {
		for (auto it = begin(); it != end(); ++it) {
			if (it->first->isAlive()) it->second->updateForce(it->first, duration);
		}

	}
	void addRegistry(ForceGenerator* fg, Entity* p) {
		insert(FRPair(p, fg));
	}
	
	void deleteParticleRegistry(Entity* p) {
		this->erase(p);
	}

	void deleteForceRegistry(ForceGenerator* f) {
		for (auto it = begin(); it != end();) {
			if (it->second == f) it = erase(it);
			else ++it;
		}

	}
	
};