#include "transformations/Transformation.h"

Transformation::Transformation() {
	M = glm::mat4(1.0f);
}

void Transformation::add(BasicTransformation* component) {
	components.push_back(component);
}

void Transformation::setTransformation(const ShaderProgram* shaderProgram) {
	for (BasicTransformation* component : components)
		component->applyTransformation(M);

	shaderProgram->sendModelMatrix(M);
}

glm::mat4 Transformation::getMatrix() const {
	return M;
}