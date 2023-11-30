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


#pragma region CONSTRUCTORAS
	Particle(Vector3 Pos, Vector3 Vel, Vector3 A, float Damping, float Masa, Vector3 Gravedad, 
		float Time, Vector4 color = { float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), 1 }, bool esModelo = false, Vector3 scale = { 0.5, 0.5, 0.5 }, GEOMETRY geometria = SPHERE);
	Particle(Vector3 Pos, Vector3 Vel, float Masa, float Time, GEOMETRY geometria = SPHERE, Vector3 scale = { 0.5, 0.5, 0.5 },
		Vector4 color = { float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), 1 }, bool esModelo = false);
	Particle(Vector3 Pos, Vector3 Vel, float Damping, float Masa, float Time, bool esMod = false,
		Vector4 color = { float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), float(rand() % 256 / 255.0f), 1 }, Vector3 scale = { 0.5, 0.5, 0.5 }, GEOMETRY geometria = SPHERE);
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
	Vector3 scale;
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
	inline int getVolume() { return scale.x * scale.y * scale.z; }
	inline int getHeight() { return scale.y; }
	inline void addGeometry(){
		switch (_myGeometry) {
			
		case SPHERE:
			forma = CreateShape(physx::PxSphereGeometry(scale.x)); break;
		case BOX:
			physx::PxBoxGeometry planeGeo(Vector3(scale.x, scale.y, scale.z));
			forma = CreateShape(planeGeo); break;

		}
	}
#pragma endregion
};

