#pragma once
#include <glm/vec3.hpp>
#include "lights/Light.h"

class SpotLight : public Light
{
private:
    int type;
    glm::vec3 position, direction, color;
    float constant_attenuation, linear_attenuation, quadratic_attenuation, cutoff, outer_cutoff;

public:
    SpotLight(const glm::vec3& sl_position, const glm::vec3& sl_direction, const glm::vec3& sl_color, float sl_constant_attenuation, float sl_linear_attenuation, float sl_quadratic_attenuation, float sl_cutoff, float sl_outer_cutoff);
    int getType() override;
    glm::vec3 getPosition() override;
    glm::vec3 getDirection() override;
    glm::vec3 getColor() override;
    float getConstantAttenuation() override;
    float getLinearAttenuation() override;
    float getQuadraticAttenuation() override;
    float getCutoff() override;
    float getOuterCutoff() override;
};