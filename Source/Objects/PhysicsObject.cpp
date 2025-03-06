#include "PhysicsObject.h"

void PhysicsObject::CalculatePostCollisionVelocity(glm::vec3& v1, glm::vec3& v2, float m1, float m2, int elasticity, glm::vec3 pos1, glm::vec3 pos2)
{
	glm::vec3 collisionNormal = (glm::normalize(pos1-pos1));

	glm::vec3 vrel = v1 - v2;
	float impulse = (-(1 + elasticity) * (glm::dot(vrel, collisionNormal))) / ((1 / m1) + (1 / m2));

	v1 = v1 + ((impulse / m1) * collisionNormal);
	v2 = v2 - ((impulse / m1) * collisionNormal);
}
