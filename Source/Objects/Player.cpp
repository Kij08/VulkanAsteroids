#include "Player.h"
#include <iostream>
#include <algorithm>
#include "../Level.h"

Player::Player()
{
	PATH_TO_MODEL = "~/../ObjectModels/CH_Player_Ship.obj";
	PATH_TO_TEXTURE = "~/../ObjectTextures/SpaceShip_CLR.png";

	Transform t;
	t.position = glm::vec3(1.f);
	t.rotation = glm::vec3(0.f, 0.f, 270.f);
	t.scale = glm::vec3(1.f);
	SetTransform(t);
	maxMoveSpeed = 30;
	shipAccel = 0.1f;
	shipDeccel = 0.2f;

	Ka = 0.005;
	Kd = 0.02;
	Ks = 0.5;
}

Player::Player(Transform t) : Object(t, "", "")
{
}

void Player::WASD_Callback(glm::vec2 keyVector)
{
	movementVector = keyVector;
}

void Player::Tick()
{
	Transform t = GetTransform();
	/*if (horizontalSpeed < maxMoveSpeed) {
		if (movementVector.x == 0 && horizontalSpeed > 0) {
			horizontalSpeed -= (time * shipDeccel * time);
			t.position.y -= horizontalSpeed;
		}
		else {
			horizontalSpeed += (time * shipAccel * time * movementVector.x);
			t.position.y += horizontalSpeed;
		}
	}
	else {
		t.position.y += horizontalSpeed;
	}
	if (verticalSpeed < maxMoveSpeed) {
		if (movementVector.y == 0 && verticalSpeed > 0) {
			verticalSpeed -= (time * shipDeccel *time);
			t.position.z -= verticalSpeed;
		}
		else {
			verticalSpeed += (time * shipAccel * time * movementVector.y);
			t.position.z += verticalSpeed;
		}
	}
	else {
		verticalSpeed -= (time * shipDeccel * time);
	}*/

	/*std::cout << movementVector.x << "\n";
	if (movementVector.x == 0) {
		if (horizontalSpeed != 0) {
			horizontalSpeed -= (GetLevel()->GetDeltaTime() * shipDeccel * GetLevel()->GetDeltaTime());
			horizontalSpeed = std::clamp(horizontalSpeed, 0.f, (float)maxMoveSpeed);
			t.position.y -= horizontalSpeed;
		}
	}
	else {
		horizontalSpeed += (GetLevel()->GetDeltaTime() * shipAccel * GetLevel()->GetDeltaTime());
		horizontalSpeed = std::clamp(horizontalSpeed, 0.f, (float)maxMoveSpeed);
		t.position.y += horizontalSpeed * movementVector.x;
	}*/

	horizontalSpeed += (GetLevel()->GetDeltaTime() * shipAccel * GetLevel()->GetDeltaTime());
	horizontalSpeed = std::clamp(horizontalSpeed, 0.f, (float)maxMoveSpeed);
	t.position.y += horizontalSpeed * movementVector.x;

	verticalSpeed += (GetLevel()->GetDeltaTime() * shipAccel * GetLevel()->GetDeltaTime());
	verticalSpeed = std::clamp(verticalSpeed, 0.f, (float)maxMoveSpeed);
	t.position.z += verticalSpeed * movementVector.y;

	t.position.y = std::clamp(t.position.y, (float)-2000, (float)2000);
	t.position.z = std::clamp(t.position.z, (float)-2000, (float)2000);

	SetTransform(t);
}
