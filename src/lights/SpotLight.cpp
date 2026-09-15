#include "lights/SpotLight.h"

SpotLight::SpotLight(const glm::vec3& sl_position, const glm::vec3& sl_direction, const glm::vec3& sl_color, float sl_constant_attenuation, float sl_linear_attenuation, float sl_quadratic_attenuation, float sl_cutoff, float sl_outer_cutoff) {
    this->position = sl_position;
    this->direction = sl_direction;
    this->color = sl_color;
    this->constant_attenuation = sl_constant_attenuation;
    this->linear_attenuation = sl_linear_attenuation;
    this->quadratic_attenuation = sl_quadratic_attenuation;
    this->cutoff = sl_cutoff;
    this->outer_cutoff = sl_outer_cutoff;
    this->type = 2;
}

int SpotLight::getType() {
    return type;
}

glm::vec3 SpotLight::getPosition() {
    return position;
}

glm::vec3 SpotLight::getDirection() {
    return direction;
}

glm::vec3 SpotLight::getColor() {
    return color;
}

float SpotLight::getConstantAttenuation() {
    return constant_attenuation;
}

float SpotLight::getLinearAttenuation() {
    return linear_attenuation;
}

float SpotLight::getQuadraticAttenuation() {
    return quadratic_attenuation;
}

float SpotLight::getCutoff() {
    return cutoff;
}

float SpotLight::getOuterCutoff() {
    return outer_cutoff;
}