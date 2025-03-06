#pragma once
#include <vector>
#include <chrono>
#include <memory>
#include "Objects/PhysicsObject.h"

class Renderer;
class Player;
class GLFWwindow;

class Level {

private:

	//List of all objects in the scene
	std::vector<std::shared_ptr<Object>> worldArray;

	void TickAllWorldObjects();
	void LevelRules();

	Renderer* renderer;
	int MainPlayerIndex;

	float deltaTime;

public:
	
	template<class T>
	int SpawnObject(bool bLit);
	
	const std::vector<std::shared_ptr<Object>>& GetWorldList() { return worldArray; };
	Player* GetMainPlayer() { return reinterpret_cast<Player*>(worldArray[MainPlayerIndex].get()); };

	void WorldInit(Renderer* r);
	void SimulateWorld();

	float GetDeltaTime() { return deltaTime; }
	void SetDeltaTime(float time) { deltaTime = time; };

	void SimulateCollision();
	void Cleanup();
};