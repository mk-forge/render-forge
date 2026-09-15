#pragma once
#include "transformations/BasicTransformation.h"

class Translation : public BasicTransformation
{
private:
	glm::vec3 translation;

public:
	explicit Translation(glm::vec3 translationVector);
	void applyTransformation(glm::mat4& M) override;
};