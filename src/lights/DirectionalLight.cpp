#include "lights/DirectionalLight.h"

DirectionalLight::DirectionalLight(const glm::vec3& dl_direction, const glm::vec3& dl_color) {
    this->direction = dl_direction;
    this->color = dl_color;
    this->type = 0;
}

int DirectionalLight::getType() {
    return type;
}

glm::vec3 DirectionalLight::getPosition() {
    return glm::vec3(0.0f);
}

glm::vec3 DirectionalLight::getDirection() {
    return direction;
}

glm::vec3 DirectionalLight::getColor() {
    return color;
}

float DirectionalLight::getConstantAttenuation() {
    return 0.0f;
}

float DirectionalLight::getLinearAttenuation() {
    return 0.0f;
}

float DirectionalLight::getQuadraticAttenuation() {
    return 0.0f;
}