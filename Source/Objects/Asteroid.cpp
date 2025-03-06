#include "Asteroid.h"
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iostream>
#include "../Level.h"

Asteroid::Asteroid()
{
	int random = rand() % 3;
	Transform t;

	SphereCol = std::make_unique<Collider>();
	SphereCol.get()->Owner = this;

	//Choose random model size. Set speed based on the size.
	switch (random) {
	case 0:
		PATH_TO_MODEL = modelList[0];
		PATH_TO_TEXTURE = textureList[0];
		t.scale = glm::vec3(0.4f);
		velocity.x = 1 + (rand() % 8);
		SphereCol.get()->radius = 3;
		break;
	case 1:
		PATH_TO_MODEL = modelList[1];
		PATH_TO_TEXTURE = textureList[1];
		t.scale = glm::vec3(0.5f);
		velocity.x = 2 + (rand() % 8);
		SphereCol.get()->radius = 4;
		break;
	case 2:
		PATH_TO_MODEL = modelList[2];
		PATH_TO_TEXTURE = textureList[2];
		t.scale = glm::vec3(0.7f);
		velocity.x = 3 + (rand() % 8);
		SphereCol.get()->radius = 5;
		break;
	}


	//Spawn in random location and rotation
	t.position = glm::vec3(-7000.f, ((rand()%4000) - 2000), ((rand() % 4000) - 2000));
	t.rotation = glm::vec3(rand() % 360, rand() % 360, rand() % 360);
	SetTransform(t);

	SphereCol.get()->position = GetTransform().position;

	//Lighting constants
	Ka = 0.008;
	Kd = 0.07;
	Ks = 0;

}

Asteroid::Asteroid(Transform t)
{
	SetTransform(t);


	int random = rand() % 3;
	switch (random) {
	case 0:
		PATH_TO_MODEL = modelList[0];
		break;
	case 1:
		PATH_TO_MODEL = modelList[1];
		break;
	case 2:
		PATH_TO_MODEL = modelList[2];
		break;
	}
}

void Asteroid::Tick()
{
	Transform t = GetTransform();
	t.position += velocity * GetLevel()->GetDeltaTime();

	t.rotation.x += (((rand() % 2)) * GetLevel()->GetDeltaTime()) / 10;
	t.rotation.x = (int)t.rotation.x % 360;
	t.rotation.y += (((rand() % 2)) * GetLevel()->GetDeltaTime()) / 10;
	t.rotation.y = (int)t.rotation.y % 360;
	t.rotation.z += (((rand() % 2)) * GetLevel()->GetDeltaTime()) / 10;
	t.rotation.z = (int)t.rotation.z % 360;
	SetTransform(t);

	if (t.position.x > 1500) {
		//Mark for destroy
		bIsDirty = true;
	}

	//Update collider position to obj position each frame
	SphereCol->position = GetTransform().position;
}

void Asteroid::CollisionOccured(PhysicsObject* otherObj)
{
	//Add velocity based on object and collision properties
	CalculatePostCollisionVelocity(this->velocity, otherObj->velocity, this->mass,
		otherObj->GetMass(), asteroidElasticity, this->GetTransform().position, otherObj->GetTransform().position);
}

bool Asteroid::CheckCollision(PhysicsObject* otherObj)
{
	return SphereCol.get()->CollisionCalc(SphereCol.get(), otherObj->GetCollider());
}

Collider* Asteroid::GetCollider()
{
	return SphereCol.get();
}
