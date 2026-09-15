#pragma once
#include <glm/mat4x4.hpp>
#include <vector>
#include "rendering/ShaderProgram.h"
#include "transformations/BasicTransformation.h"

class ShaderProgram;

class Transformation
{
private:
	std::vector<BasicTransformation*> components;
	glm::mat4 M;

public:
	Transformation();
	void add(BasicTransformation* component);
	void setTransformation(const ShaderProgram* shaderProgram);
	glm::mat4 getMatrix() const;
};