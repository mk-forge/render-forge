#include "objects/Tree.h"

void Tree::draw(VAO& VAO) {
	VAO.bindVAO();
	glDrawArrays(GL_TRIANGLES, 0, 92814);
	VAO.unbindVAO();
}