#include "Level.h"
#include "Objects/Player.h"
#include "Objects/Asteroid.h"
#include <cstdlib>
#include <ctime>
#include "Renderer.h"
#include "PrimitiveTypes/Window.h"
#include <iostream>
#include <random>
#include "Objects/Skybox.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* win = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
	static glm::vec2 prevMoveVec;
	glm::vec2 moveVec = prevMoveVec;

	if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
		if (moveVec.y != -1) {
			moveVec.y = 0;
		}
	}
	if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
		if (moveVec.x != 1) {
			moveVec.x = 0;
		}
	}
	if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
		if (moveVec.y != 1) {
			moveVec.y = 0;
		}
	}
	if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
		if (moveVec.x != -1) {
			moveVec.x = 0;
		}
	}

	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		moveVec.y = 1.f;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		moveVec.x = -1.f;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		moveVec.y = -1.f;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		moveVec.x = 1.f;
	}

	win->level->GetMainPlayer()->WASD_Callback(moveVec);
	prevMoveVec = moveVec;
}


void Level::TickAllWorldObjects()
{
	for (const auto& object : worldArray) {
		object->Tick();
	}
	
}

template<class T>
int Level::SpawnObject(bool bLit)
{
	static_assert(std::is_base_of<Object, T>::value, "Can only spawn objects!");

	std::shared_ptr<Object> obj = std::make_shared<T>();

	//Store the objects vertex buffer offset and size 

	int vertexOffset, indexOffset, objVertSize, objIndexSize;
	renderer->LoadModel(vertexOffset, indexOffset, objVertSize, objIndexSize, obj->GetModelPath());
	obj.get()->SetVertOffset(vertexOffset);
	obj.get()->SetIndexOffset(indexOffset);
	obj.get()->SetVertSizeInBuffer(objVertSize);
	obj.get()->SetIndexSizeInOffset(objIndexSize);

	//Store obj texture buffer index and size

	int objTextureIndex;
	renderer->LoadTexture(obj->GetTexturePath(), objTextureIndex);
	obj.get()->SetDescriptorSetIndex(objTextureIndex);
	obj.get()->SetLevelReference(this);

	obj->bIsLit = bLit;

	worldArray.push_back(std::move(obj));

	//return spawned object index in world array
	return worldArray.size() - 1;
}

void Level::WorldInit(Renderer* r)
{
	srand(static_cast <unsigned> (time(0)));

	renderer = r;
	SpawnObject<Skybox>(false);

	MainPlayerIndex = SpawnObject<Player>(true);

	SpawnObject<Asteroid>(true);

	glfwSetKeyCallback(r->GetWindow(), key_callback);
}

void Level::SimulateWorld()
{
	TickAllWorldObjects();
	SimulateCollision();
	LevelRules();
	Cleanup();
}

void Level::LevelRules()
{
	//Generate random number between 1 and 100
	//if it equals spawn an asteroid
	float randAsteroid = 1 + (rand() % 1001);   // v2 in the range 1 to 100
	if (randAsteroid < 80) {
		std::cout << "Spawn Asteroid" << randAsteroid << "\n";
		
		SpawnObject<Asteroid>(true);
	}
}


void Level::SimulateCollision()
{
	//Add cache and custom world array adder. only when world array is updated will the cache update
	//Broad phase
	std::vector<PhysicsObject*> physicsObjects;
	for (const auto& obj : worldArray) {
		if (PhysicsObject* pObj = dynamic_cast<PhysicsObject*>(obj.get())) {
			physicsObjects.push_back(pObj);
		}
	}

	//Narrow phase
	for (int i = 0; i < physicsObjects.size(); i++) {
		for (int j = 0; j < physicsObjects.size(); j++) {
			physicsObjects[i]->CheckCollision(physicsObjects[j]);
		}
	}
}

void Level::Cleanup()
{
	//Reset all obj ptrs that are marked dirty
	for (int i = 0; i < worldArray.size(); i++) {
		if (worldArray[i].get()->bIsDirty) {
			worldArray[i].reset();
		}
	}
}
