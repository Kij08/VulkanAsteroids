#pragma once
#include "Object.h"

class Player : public Object {
public:
	Player();
	Player(Transform t);

	void WASD_Callback(glm::vec2 keyVector);

private:
	virtual void Tick();

	int maxMoveSpeed;
	float horizontalSpeed;
	float verticalSpeed;
	float shipAccel;
	float shipDeccel;

	glm::vec2 movementVector;
};