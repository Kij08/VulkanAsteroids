#pragma once
#include "PhysicsObject.h"
#include <memory>

class Asteroid : public PhysicsObject {
public:
	Asteroid();
	Asteroid(Transform t);

private:
	const std::vector<std::string> modelList = { 
		"~/../ObjectModels/SM_Asteroid_LRG_A.obj",
		"~/../ObjectModels/SM_Asteroid_MED_A.obj",
		"~/../ObjectModels/SM_Asteroid_SML_A.obj"
	};

	const std::vector<std::string> textureList = {
		"~/../ObjectTextures/Asteroid_LRG_CLR.png",
		"~/../ObjectTextures/Asteroid_MED_CLR.png",
		"~/../ObjectTextures/Asteroid_SML_CLR.png"
	};

	int asteroidSpeed;
	const float asteroidElasticity = 0.6f;

	virtual void Tick() override;

	std::unique_ptr<Collider> SphereCol;

	virtual void CollisionOccured(PhysicsObject* otherObj) override;

	virtual bool CheckCollision(PhysicsObject* otherObj) override;

	virtual Collider* GetCollider() override;
};