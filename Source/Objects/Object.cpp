#include "Object.h"
#include "../Renderer.h"
#include "../Level.h"


Object::Object()
{
	modelVertexStartOffset = -1;
	modelVertexSizeInBuffer = -1;
	modelIndexStartOffset = -1;
	modelIndexSizeInBuffer = -1;

	bIsLit = true;
}

Object::Object(Transform t, std::string model, std::string tex)
{
	SetTransform(t);
	PATH_TO_MODEL = model;
	PATH_TO_TEXTURE = tex;

	modelVertexStartOffset = -1;
	modelVertexSizeInBuffer = -1;
	modelIndexStartOffset = -1;
	modelIndexSizeInBuffer = -1;

	//Add a default box extent
	BoundingBox boundingBox;
	boundingBox.bIsTrigger = true;
	boundingBox.boxExtentFace1 = glm::vec4(1.f, 1.f, 1.f, 1.f);
	boundingBox.boxExtentFace2 = glm::vec4(1.f, 1.f, 1.f, 1.f);
	boundingBoxes.push_back(boundingBox);

	Ka = 0;
	Kd = 0;
	Ks = 0;
}

void Object::Tick()
{
}
