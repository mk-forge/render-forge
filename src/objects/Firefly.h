#pragma once
#include <glm/vec3.hpp>

class Firefly {
private:
    glm::vec3 position, origin;
    float phase, speed, radius;

public:
    Firefly();
    Firefly(const glm::vec3& origin, float phase, float speed, float radius);
    glm::vec3 getPosition() const;
    void update(float deltaTime);
};