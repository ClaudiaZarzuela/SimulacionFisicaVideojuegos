#pragma once
#include "RenderUtils.hpp"
#include <list>
class FireworkGenerator;

class Particle
{
public: 
	enum GEOMETRY {
		SPHERE = 0, BOX = 1
	};

	static const float RANDOM;

#pragma region CONSTRUCTORAS
	Particle(Vector3 Pos, Vector3 Vel, Vector3 A, float Damping, float Masa, Vector3 Gravedad, 
		float Time, Vector4 color = { RANDOM, RANDOM, RANDOM, 1 }, bool esModelo = false, double scale = 0.5, GEOMETRY geometria = SPHERE);
	Particle(Vector3 Pos, Vector3 Vel, float Masa, float Time, GEOMETRY geometria = SPHERE,
		Vector4 color = { RANDOM, RANDOM, RANDOM, 1 }, bool esModelo = false, double scale = 0.5);
	Particle(Vector3 Pos, Vector3 Vel, float Damping, float Masa, float Time, bool esMod = false,
		Vector4 color = { RANDOM, RANDOM, RANDOM, 1 }, double scale = 0.5, GEOMETRY geometria = SPHERE);
#pragma endregion

	~Particle();

#pragma region PARAMETROS
	physx::PxTransform _pose;
	Vector3 _vel;
	Vector3 a;
	physx::PxShape* forma;
	Vector4 _color;
	Vector3 gravedad = Vector3(0,-10,0);
	float time = 0;
	float maxTime;
	float damping = 0.998;
	float mass;
	float _inv_mass;
	//float _inv_mass;
	bool alive = true;
	bool esModelo;
	double scale;
	Vector3 force = Vector3(0, 0, 0);
	RenderItem* renderItem = nullptr;
	FireworkGenerator* _gen = nullptr;
	GEOMETRY _myGeometry;
#pragma endregion

#pragma region METODOS
	void integrate(double t);
	bool isAlive() { return alive; }
	virtual Particle* clone() const;
	void setPos(Vector3 p) { _pose = physx::PxTransform(p); }
	bool generatesOnDeath();
	inline Vector3 getVel() { return _vel; }
	virtual std::list<Particle*> explode() { return std::list<Particle*>(); }
	inline void clearForce() { force *= 0.0; }
	inline void addForce(const Vector3& f) { force += f; }
	inline void addGeometry(){
		switch (_myGeometry) {
			
		case SPHERE:
			forma = CreateShape(physx::PxSphereGeometry(scale)); break;
		case BOX:
			physx::PxBoxGeometry planeGeo(Vector3(scale*2, scale*2, scale*2));
			forma = CreateShape(planeGeo); break;

		}
	}
#pragma endregion

};

