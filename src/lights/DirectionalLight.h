#pragma once
#include <glm/vec3.hpp>
#include "lights/Light.h"

class DirectionalLight : public Light
{
private:
	int type;
	glm::vec3 direction, color;

public:
	DirectionalLight(const glm::vec3& dl_direction, const glm::vec3& dl_color);
	int getType() override;
	glm::vec3 getPosition() override;
	glm::vec3 getDirection() override;
	glm::vec3 getColor() override;
	float getConstantAttenuation() override;
	float getLinearAttenuation() override;
	float getQuadraticAttenuation() override;
};