#include "objects/SkyCube.h"

void SkyCube::draw(VAO& VAO) {
	VAO.bindVAO();
	glDrawArrays(GL_TRIANGLES, 0, 108);
	VAO.unbindVAO();
}