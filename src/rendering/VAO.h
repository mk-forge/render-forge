#pragma once
#include "VBO.h"

class VAO
{
private:
	GLuint ID = 0;

public:
	VAO();
	void linkVBO(VBO VBO, GLuint layout) const;
	void bindVAO() const;
	void unbindVAO() const;
	void deleteVAO() const;
};