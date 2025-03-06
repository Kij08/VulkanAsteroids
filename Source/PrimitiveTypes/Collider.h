#pragma once
#include <glm.hpp>

class PhysicsObject;

class Collider {

public:

	//Should be valid for the whole lifetime of collider
	PhysicsObject* Owner;
	float radius;
	glm::vec3 position;

	bool CollisionCalc(Collider* collider, Collider* colidee);
	//bool CollisionCalc(Sphere* collider, Capsule* colidee);
};

class Sphere : public Collider {
	float radius;
	glm::vec3 position;

};

class Capsule : public Collider {
	float radius;
	float height;
	glm::vec3 position;
};