#pragma once
#include <list>
#include "Entity.h"

class FireworkGenerator;

class Particle: public Entity
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

	virtual ~Particle();

#pragma region PARAMETROS
	Vector3 a;
	Vector3 gravedad = Vector3(0,-10,0);
	float damping = 0.998;
	FireworkGenerator* _gen = nullptr;
	GEOMETRY _myGeometry;
#pragma endregion

#pragma region METODOS
	virtual void integrate(double t)override;
	virtual Particle* clone() const;
	virtual void setPosition(Vector3 p)override { _pose = physx::PxTransform(p); }
	virtual void setVelocity(Vector3 Vel) override {};
	virtual bool generatesOnDeath()override;
	inline Vector3 getVel() { return _vel; }
	virtual std::list<Entity*> explode() { return std::list<Entity*>(); }
	inline void clearForce() { force *= 0.0; }
	virtual void addForce(const Vector3& f) override{ force += f; }
	inline void addGeometry(){
		switch (_myGeometry) {
			
		case SPHERE:
			_shape = CreateShape(physx::PxSphereGeometry(_scale.x)); break;
		case BOX:
			physx::PxBoxGeometry planeGeo(Vector3(_scale.x, _scale.y, _scale.z));
			_shape = CreateShape(planeGeo); break;

		}
	}
	inline void changeMass(char key) {
		if(key == 'm')mass += 100;
		else {
			if (mass - 100 > 0) mass -= 100;
			else mass = 1;
		}
	}
	inline void changeVolume(char key) {
		if (key == 'b')_scale += {0.5,0.5,0.5};
		else {
			Vector3 aux = _scale;
			aux -= {0.5, 0.5, 0.5};
			if (aux.x <= 0 || aux.y <= 0 || aux.z <= 0) _scale -= {0.5, 0.5, 0.5};
			else _scale = { 1,1,1 };
		}
	}
	virtual Vector3 getPosition() { return _pose.p; }
#pragma endregion
};

