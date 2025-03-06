#pragma once

class GLFWwindow;
class Level;
class Renderer;

class Window {
public:
	GLFWwindow* window;
	Level* level;
	Renderer* rend;

	Window(Level* lvl, Renderer* r) {
		level = lvl;
		rend = r;
	}
};