#include "objects/Sphere.h"

void Sphere::draw(VAO& VAO) {
	VAO.bindVAO();
	glDrawArrays(GL_TRIANGLES, 0, 2880);
	VAO.unbindVAO();
}