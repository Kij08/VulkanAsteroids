#include "Collider.h"
#include "../Objects/PhysicsObject.h"

bool Collider::CollisionCalc(Collider* collider, Collider* colidee) {
	
	float dist = glm::distance(collider->position, colidee->position);

	if (dist <= collider->radius + colidee->radius) {
		if (Owner) {
			
			//Correct object position
			glm::vec3 collisionDirection = glm::normalize(collider->position - colidee->position);
			float offset = dist - (collider->radius + colidee->radius);
			Transform T = Owner->GetTransform();
			T.position += collisionDirection * offset;
			Owner->SetTransform(T);
			
			//Notify Collision
			Owner->CollisionOccured(colidee->Owner);
		}
		return true;
	}

	return false;
}