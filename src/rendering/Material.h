#pragma once
#include <GL/glew.h>

class Material
{
private:
	float reflection_ambient = 1.0f;
	float reflection_diffuse = 1.0f;
	float reflection_specular = 1.0f;

public:
	Material(float reflectionAmbient, float reflectionDiffuse, float reflectionSpecular);
	float getReflectionAmbient() const;
	float getReflectionDiffuse() const;
	float getReflectionSpecular() const;
};