#include "ShaderLoader.h"

std::string ShaderLoader::loadFile(const char* fname) const {
	std::ifstream file(fname);
	if (!file.is_open())
		fprintf(stderr, "ERROR: Unable to open file %s\n", fname);

	std::stringstream fileData;
	fileData << file.rdbuf();
	file.close();
	return fileData.str();
}

GLuint ShaderLoader::loadShader(const char* vertexFile, const char* fragmentFile) {
	std::string vertexShaderString = loadFile(vertexFile);
	std::string fragmentShaderString = loadFile(fragmentFile);
	GLint vlen = (GLint)vertexShaderString.length();
	GLint flen = (GLint)fragmentShaderString.length();

	if (vertexShaderString.empty()) fprintf(stderr, "ERROR: Empty Vertex Shader\n");
	if (fragmentShaderString.empty()) fprintf(stderr, "ERROR: Empty Fragment Shader\n");

	const char* vertexShaderCStr = vertexShaderString.c_str();
	const char* fragmentShaderCStr = fragmentShaderString.c_str();

	vertexID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexID, 1, (const GLchar**)&vertexShaderCStr, &vlen);
	glCompileShader(vertexID);
	GLint status;
	glGetShaderiv(vertexID, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(vertexID, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<GLchar> strInfoLog(infoLogLength + 1);
		glGetShaderInfoLog(vertexID, infoLogLength, nullptr, strInfoLog.data());
		fprintf(stderr, "ERROR: Compile failure in Vertex shader:\n%s\n", strInfoLog.data());
	}

	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentID, 1, (const GLchar**)&fragmentShaderCStr, (int*)&flen);
	glCompileShader(fragmentID);
	glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetShaderiv(fragmentID, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<GLchar> strInfoLog(infoLogLength + 1);
		glGetShaderInfoLog(fragmentID, infoLogLength, nullptr, strInfoLog.data());
		fprintf(stderr, "ERROR: Compile failure in Fragment shader:\n%s\n", strInfoLog.data());
	}

	shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexID);
	glAttachShader(shaderProgramID, fragmentID);
	glLinkProgram(shaderProgramID);
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &status);

	if (status == GL_FALSE) {
		GLint infoLogLength;
		glGetProgramiv(shaderProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<GLchar> strInfoLog(infoLogLength + 1);
		glGetProgramInfoLog(shaderProgramID, infoLogLength, nullptr, strInfoLog.data());
		fprintf(stderr, "ERROR: Linker failure: %s\n", strInfoLog.data());
	}

	return shaderProgramID;
}

void ShaderLoader::deleteShader() const {
	glDetachShader(shaderProgramID, vertexID);
	glDetachShader(shaderProgramID, fragmentID);
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
	glUseProgram(0);
	glDeleteProgram(this->shaderProgramID);
}

ShaderLoader::ShaderLoader(const char* vertexFile, const char* fragmentFile, GLuint* shaderID) {
	*shaderID = loadShader(vertexFile, fragmentFile);
}