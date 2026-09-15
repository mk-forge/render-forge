#include "VBO.h"

VBO::VBO(const float* vertices, int size) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

void VBO::bindVBO() const {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::unbindVBO() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::deleteVBO() const {
	glDeleteBuffers(1, &ID);
}

void VBO::configure2Attributes() const {
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	bindVBO();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)nullptr);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	unbindVBO();
}

void VBO::configure3Attributes() const {
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	bindVBO();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)nullptr);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float)));
	unbindVBO();
}