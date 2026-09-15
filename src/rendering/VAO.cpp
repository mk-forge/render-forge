#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &ID);
}

void VAO::linkVBO(VBO VBO, GLuint layout) const {
	VBO.bindVBO();
	glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr);
	glEnableVertexAttribArray(layout);
	VBO.unbindVBO();
}

void VAO::bindVAO() const {
	glBindVertexArray(ID);
}

void VAO::unbindVAO() const {
	glBindVertexArray(0);
}

void VAO::deleteVAO() const {
	glDeleteVertexArrays(1, &ID);
}