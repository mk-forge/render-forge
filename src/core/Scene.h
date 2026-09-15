#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "rendering/ShaderProgram.h"
#include "rendering/VAO.h"
#include "rendering/VBO.h"
#include "objects/Sphere.h"
#include "objects/Tree.h"
#include "transformations/Transformation.h"
#include "transformations/Rotation.h"
#include "transformations/DynamicRotation.h"
#include "transformations/Translation.h"
#include "transformations/Scale.h"
#include "Camera.h"
#include <time.h>
#include "patterns/Subject.h"
#include "Callback.h"
#include "objects/Bush.h"
#include "objects/Plain.h"
#include "objects/SkyCube.h"
#include "objects/ModelAssimp.h"
#include "objects/Firefly.h"
#include "data/plain.model"
#include "data/tree.model"
#include "data/bush.model"
#include "data/sphere.model"
#include "data/skycube.model"
#include <random>
#include <memory>

#define GLM_ENABLE_EXPERIMENTAL

class Scene
{
private:
    VAO VAO_sphere, VAO_tree, VAO_bush, VAO_plain, VAO_skycube;
    VBO VBO_sphere, VBO_tree, VBO_bush, VBO_plain, VBO_skycube;
    Sphere sphere1, sphere2, sphere3, sphere4;
    std::vector<std::unique_ptr<Tree>> trees;
    std::vector<std::unique_ptr<Bush>> bushes;
    std::vector<ModelAssimp> zombies;
    std::vector<Firefly> fireflies;
    Plain grass;
    ShaderProgram* shaderProgram, *constant, *lambert, *phong, *blinn, *texture, *cubemap, *assimp;
    Camera camera;
    ModelAssimp modelHouse, modelFence, modelFirefly, modelSun, modelEarth, modelMoon;

    std::array<float, 50> treePositionX;
    std::array<float, 50> treePositionZ;
    std::array<float, 50> treeScale;
    std::array<float, 5> zombiePositionX;
    std::array<float, 5> zombiePositionZ;
    int chosenScene = 0;
    double angle = 0.0;
    float deltaTime = 0.0f;

public:
    Scene();
    void renderScene(int scene);
    void drawForestScene();
    void drawSphereScene();
    void drawPlanetScene();
    void run(GLFWwindow* window);
    void initialize();
    void drawSky();
    void createShaders();
    void destroy();
};