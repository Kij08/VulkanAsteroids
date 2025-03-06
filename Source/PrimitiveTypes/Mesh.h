#pragma once

#include "glm.hpp"
#include <vector>

class Mesh {
public:
	struct MeshData {
		glm::vec3 pos;
		glm::vec3 colour;
		glm::vec2 uv;
		glm::vec3 normal;
	};

	std::vector<MeshData> vertices;
	std::vector<uint32_t> indices;
};