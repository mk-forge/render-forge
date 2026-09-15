#pragma once
#include "transformations/BasicTransformation.h"

class DynamicRotation : public BasicTransformation
{
private:
	glm::vec3 axis;
	
public:
	explicit DynamicRotation(glm::vec3 rotationAxis);
	void applyTransformation(glm::mat4& matrix) override;
};