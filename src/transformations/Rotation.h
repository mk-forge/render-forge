#pragma once
#include "transformations/BasicTransformation.h"

class Rotation : public BasicTransformation
{
private:
	float angle = 0.0f;
	glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);

public:
	Rotation() = default;
	Rotation(float rotationAngle, glm::vec3 rotationAxis);
	void applyTransformation(glm::mat4& M) override;
};