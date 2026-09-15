#pragma once
#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

class VBO
{
private:
	GLuint ID = 0;

public:
	VBO() = default;
	explicit VBO(const float* vertices, int size);
	void bindVBO() const;
	void unbindVBO() const;
	void deleteVBO() const;
	void configure2Attributes() const;
	void configure3Attributes() const;
};