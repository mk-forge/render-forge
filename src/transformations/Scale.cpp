#include "transformations/Scale.h"

Scale::Scale(glm::vec3 scaleVector) {
	this->scale = scaleVector;
}

void Scale::applyTransformation(glm::mat4& M) {
	M = glm::scale(M, scale);
}