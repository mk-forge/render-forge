#pragma once
#include <glm/vec3.hpp>
#include "lights/Light.h"

class PointLight : public Light
{
private:
    int type;
    glm::vec3 position, color;
    float constant_attenuation, linear_attenuation, quadratic_attenuation;

public:
    PointLight(const glm::vec3& pl_position, const glm::vec3& pl_color, float pl_constant_attenuation, float pl_linear_attenuation, float pl_quadratic_attenuation);
    int getType() override;
    glm::vec3 getPosition() override;
    glm::vec3 getDirection() override;
    glm::vec3 getColor() override;
    float getConstantAttenuation() override;
    float getLinearAttenuation() override;
    float getQuadraticAttenuation() override;
    void setPosition(const glm::vec3& newPosition);
};