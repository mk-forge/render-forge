#include "lights/PointLight.h"

PointLight::PointLight(const glm::vec3& pl_position, const glm::vec3& pl_color, float pl_constant_attenuation, float pl_linear_attenuation, float pl_quadratic_attenuation) {
    this->position = pl_position;
    this->color = pl_color;
    this->constant_attenuation = pl_constant_attenuation;
    this->linear_attenuation = pl_linear_attenuation;
    this->quadratic_attenuation = pl_quadratic_attenuation;
    this->type = 1;
}

int PointLight::getType() {
    return type;
}

glm::vec3 PointLight::getPosition() {
    return position;
}

glm::vec3 PointLight::getDirection() {
    return glm::vec3(0.0f);
}

glm::vec3 PointLight::getColor() {
    return color;
}

float PointLight::getConstantAttenuation() {
    return constant_attenuation;
}

float PointLight::getLinearAttenuation() {
    return linear_attenuation;
}

float PointLight::getQuadraticAttenuation() {
    return quadratic_attenuation;
}

void PointLight::setPosition(const glm::vec3& newPosition) {
    this->position = newPosition;
}