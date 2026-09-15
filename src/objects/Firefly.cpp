#include "objects/Firefly.h"
#include <cmath>

Firefly::Firefly() : position(0.0f), origin(0.0f), phase(0.0f), speed(1.0f), radius(1.0f) {
}

Firefly::Firefly(const glm::vec3& origin, float phase, float speed, float radius) : position(origin), origin(origin), phase(phase), speed(speed), radius(radius) {
}

glm::vec3 Firefly::getPosition() const {
    return position;
}

void Firefly::update(float deltaTime) {
    phase += speed * deltaTime;
    position.x = origin.x + std::sin(phase) * radius;
    position.z = origin.z + std::cos(phase * 0.7f) * radius;
    position.y = origin.y + std::sin(phase * 1.3f) * 0.5f;
}