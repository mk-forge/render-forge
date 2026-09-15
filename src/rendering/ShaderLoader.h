#pragma once
#include <GL/glew.h>
#include <string.h> 
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

class ShaderLoader
{
private:
	GLuint vertexID = 0;
	GLuint fragmentID = 0;
	GLuint shaderProgramID = 0;
	std::string loadFile(const char* fname) const;

public:
	GLuint loadShader(const char* vertexFile, const char* fragmentFile);
	void deleteShader() const;
	ShaderLoader() = default;
	ShaderLoader(const char* vertexFile, const char* fragmentFile, GLuint* shaderID);
	~ShaderLoader() = default;
};