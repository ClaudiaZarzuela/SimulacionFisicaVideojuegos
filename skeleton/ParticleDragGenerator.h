#pragma once
#include "ForceGenerator.h"
#include "core.hpp"
#include "Plane.h"
class ParticleDragGenerator : public ForceGenerator
{
protected:
	float _k1; //Coef for velocity
	float _k2; // Coef for square velocity
	Plane* plane = nullptr;
	float height;
	Vector3 _pos;
	Vector3 _dim;
	Vector3 _wind;
public:
	ParticleDragGenerator(Vector3 pos, Vector3 Dimensions, float h, double duration = -1e10){ _duration = duration; _name = "WIND"; plane = new Plane(pos, Dimensions); _pos = pos; _dim = Dimensions;  height = h; }
	ParticleDragGenerator(Vector3 pos, Vector3 Dimensions, float h, Vector3 vel, double duration = -1e10) :ForceGenerator() { _duration = duration; _name = "WIND"; plane = new Plane(pos, Dimensions); _pos = pos; _dim = Dimensions;  height = h; _wind = vel; }
	ParticleDragGenerator(const float k1, const float k2, Vector3 pos, Vector3 Dimensions, float h, Vector3 vel, double duration = -1e10) :ForceGenerator() { _duration = duration; _name = "WIND"; setDrag(k1, k2); plane = new Plane(pos, Dimensions); _pos = pos; _dim = Dimensions; height = h; _wind = vel;}
	virtual void updateForce(Particle* particle, double t) ;
	inline void setDrag(float k1, float k2) { _k1 = k1; _k2 = k2; }
	inline float getK1() { return _k1;}
	inline float getK2() { return _k2;}
	bool insideBoundingBox(Vector3 pos);
	~ParticleDragGenerator() { delete(plane); }
	virtual inline void activateForce() override {
		active = !active;
		if (active) {
			std::cout << "DRAG FORCE: ACTIVATED" << std::endl;
		}
		else {
			std::cout << "DRAG FORCE: DEACTIVATED" << std::endl;
		}
	}
};

