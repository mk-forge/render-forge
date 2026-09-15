#include "Material.h"

Material::Material(float reflectionAmbient, float reflectionDiffuse, float reflectionSpecular) {
	this->reflection_ambient = reflectionAmbient;
	this->reflection_diffuse = reflectionDiffuse;
	this->reflection_specular = reflectionSpecular;
}

float Material::getReflectionAmbient() const {
	return reflection_ambient;
}

float Material::getReflectionDiffuse() const {
	return reflection_diffuse;
}

float Material::getReflectionSpecular() const {
	return reflection_specular;
}