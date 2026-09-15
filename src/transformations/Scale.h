#pragma once
#include "transformations/BasicTransformation.h"

class Scale : public BasicTransformation
{
private:
	glm::vec3 scale;

public:
	explicit Scale(glm::vec3 scaleVector);
	void applyTransformation(glm::mat4& M) override;
};