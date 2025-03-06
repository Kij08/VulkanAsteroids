#pragma once
#include "Object.h"
#include "../PrimitiveTypes/Collider.h"


class PhysicsObject : public Object {

protected:

	float mass;

	//Calculate the velocity of 2 colliding objects
	void CalculatePostCollisionVelocity(glm::vec3& v1, glm::vec3& v2, float m1, float m2, int elasticity, glm::vec3 pos1, glm::vec3 pos2);

public:

	glm::vec3 velocity;
	float GetMass() { return mass; }

	//Collision callback for objects
	virtual void CollisionOccured(PhysicsObject* otherObj);

	virtual bool CheckCollision(PhysicsObject* otherObj);

	virtual Collider* GetCollider();
};