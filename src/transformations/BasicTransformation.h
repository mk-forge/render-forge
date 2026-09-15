#pragma once
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/mat4x4.hpp>

class BasicTransformation
{
public:
    virtual ~BasicTransformation() = default;
    virtual void applyTransformation(glm::mat4& M) = 0;
};