#pragma once
#include "Object.h"

class Skybox : public Object {
public:
	Skybox() {
		PATH_TO_MODEL = "~/../ObjectModels/Space_Sphere.obj";
		PATH_TO_TEXTURE = "~/../ObjectTextures/Space_CLR.png";
		Transform t;
		t.position = glm::vec3(1.f);
		t.rotation = glm::vec3(0.f);
		t.scale = glm::vec3(0.5f);
		SetTransform(t);
		Ka = 0;
		Kd = 0;
		Ks = 0;
	}
};