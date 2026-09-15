#include "objects/Bush.h"

void Bush::draw(VAO& VAO) {
	VAO.bindVAO();
	glDrawArrays(GL_TRIANGLES, 0, 8730);
	VAO.unbindVAO();
}