#include "objects/Plain.h"

void Plain::draw(VAO& VAO) {
	VAO.bindVAO();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	VAO.unbindVAO();
}