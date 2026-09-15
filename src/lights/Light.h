#pragma once
#include <glm/glm.hpp>

class Light
{
public:
	virtual int getType() = 0;
	virtual glm::vec3 getPosition() = 0;
	virtual glm::vec3 getDirection() = 0;
	virtual glm::vec3 getColor() = 0;
	virtual float getConstantAttenuation() = 0;
	virtual float getLinearAttenuation() = 0;
	virtual float getQuadraticAttenuation() = 0;
	virtual float getCutoff();
	virtual float getOuterCutoff();
	virtual ~Light() = default;
};