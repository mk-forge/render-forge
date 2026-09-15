#include "transformations/Translation.h"

Translation::Translation(glm::vec3 translationVector) {
	this->translation = translationVector;
}

void Translation::applyTransformation(glm::mat4& M) {
	M = glm::translate(M, translation);
}