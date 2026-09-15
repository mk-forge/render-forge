#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory>
#include "Callback.h"
#include "Scene.h"

class Application
{
private:
    GLFWwindow* window;
    std::unique_ptr<Scene> scene;

public:
    Application() = default;
    void initialize();
    void createShaders();
    void run();
    [[noreturn]] void destroy();
};