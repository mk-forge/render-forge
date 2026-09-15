#include "transformations/Rotation.h"

Rotation::Rotation(float rotationAngle, glm::vec3 rotationAxis) {
	this->angle = rotationAngle;
	this->axis = rotationAxis;
}

void Rotation::applyTransformation(glm::mat4& M) {
	M = glm::rotate(M, angle, axis);
}