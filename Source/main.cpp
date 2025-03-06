#pragma once
#include "Renderer.h"
#include "Level.h"
#include "PrimitiveTypes/Window.h"


void mainLoop(Renderer* r, Level* lvl) {
	lvl->WorldInit(r);
	while (!glfwWindowShouldClose(r->GetWindow())) {
		std::chrono::steady_clock::time_point frameStartTime = std::chrono::steady_clock::now();
		//UpdateKeyboardEvents()
		//Get keyVectos and update porjected transform of player object

		//Run world sim tick (eg. checking asteroid spawn, moving all asteroids forward, checking player bounds in screen
		lvl->SimulateWorld();
		//Collision simulation
		glfwPollEvents();

		//lvl->SimulateWorld();
		r->DrawFrame(lvl->GetWorldList());

		std::chrono::steady_clock::time_point frameEndTime = std::chrono::steady_clock::now();

		lvl->SetDeltaTime(std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(frameEndTime - frameStartTime).count());
	}

	vkDeviceWaitIdle(r->GetDevice());
}

int main() {
	Renderer r;
	Level level;

	Window win(&level, &r);

	r.Startup(&win);

	mainLoop(&r, &level);

	r.Terminate();
}