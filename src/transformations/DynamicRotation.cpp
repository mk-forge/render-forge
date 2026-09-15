#include "transformations/DynamicRotation.h"

DynamicRotation::DynamicRotation(glm::vec3 rotationAxis) {
	this->axis = rotationAxis;
}

void DynamicRotation::applyTransformation(glm::mat4& matrix) {
	matrix = glm::rotate(matrix, glm::radians((float)glfwGetTime() * 20.0f), axis);
}