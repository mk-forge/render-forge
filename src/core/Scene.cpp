#include "Scene.h"

Scene::Scene() {
    trees.reserve(50);
    bushes.reserve(50);

    for (int i = 0; i < 50; i++) {
        trees.push_back(std::make_unique<Tree>());
        bushes.push_back(std::make_unique<Bush>());
    }

    static thread_local std::mt19937 treeGen(std::random_device{}());
    std::uniform_int_distribution treePositionDistribution(-20, 29);
    std::uniform_real_distribution<> treeScaleDistribution(0.5f, 1.5f);

    for (int i = 0; i < 50; i++) {
        do {
            treePositionX[i] = (float)treePositionDistribution(treeGen);
            treePositionZ[i] = (float)treePositionDistribution(treeGen);
        } while ((std::abs(treePositionX[i]) < 15.0f && std::abs(treePositionZ[i]) < 15.0f) || (treePositionX[i] < -25.0f || treePositionX[i] > 35.0f) || (treePositionZ[i] < -25.0f || treePositionZ[i] > 35.0f));
        treeScale[i] = (float)treeScaleDistribution(treeGen);
    }

    static thread_local std::mt19937 zombieGen(std::random_device{}());
    std::uniform_int_distribution zombieOffsetDistribution(-5, 5);

    for (int i = 0; i < 5; i++) {
        do {
            zombiePositionX[i] = treePositionX[i] + (float)zombieOffsetDistribution(zombieGen);
            zombiePositionZ[i] = treePositionZ[i] + (float)zombieOffsetDistribution(zombieGen);
        } while ((std::abs(zombiePositionX[i]) < 15.0f && std::abs(zombiePositionZ[i]) < 15.0f) || (zombiePositionX[i] < -20.0f || zombiePositionX[i] > 30.0f) || (zombiePositionZ[i] < -20.0f || zombiePositionZ[i] > 30.0f));
    }

    fireflies.emplace_back(glm::vec3(-8.0f, 1.0f, -8.0f), 0.0f, 5.0f, 3.0f);
    fireflies.emplace_back(glm::vec3(12.0f, 1.0f, 8.0f), 2.0f, 6.0f, 4.0f);
    fireflies.emplace_back(glm::vec3(5.0f, 1.0f, 15.0f), 4.0f, 4.0f, 2.5f);
}

void Scene::renderScene(int scene) {
    static bool firstLoad = true;
    if (firstLoad) {
        cubemap->loadSkyCube("textures/skybox/day");
        firstLoad = false;
    }

    static int lastScene = -1;
    if (scene != lastScene) {
        if (scene == 0 || scene == 2)
            cubemap->switchSkyCube("textures/skybox/night");
        else
            cubemap->switchSkyCube("textures/skybox/day");
        
        lastScene = scene;
    }

    bool spotLightEnabled = (scene != 1);
    phong->setSpotLightEnabled(spotLightEnabled);
    lambert->setSpotLightEnabled(spotLightEnabled);
    blinn->setSpotLightEnabled(spotLightEnabled);

    bool directionalLightOnly = (scene == 1);
    phong->setDirectionalLightOnly(directionalLightOnly);
    lambert->setDirectionalLightOnly(directionalLightOnly);
    blinn->setDirectionalLightOnly(directionalLightOnly);

    if (scene == 0)
        drawForestScene();
    else if (scene == 1)
        drawSphereScene();
    else if (scene == 2)
        drawPlanetScene();
}

void Scene::drawForestScene() {
    drawSky();
    blinn->update();

    for (int i = 0; i < 50; i++) {
        Transformation t_tree;
        Translation tr_tree(glm::vec3(treePositionX[i], 0.0f, treePositionZ[i]));
        Scale s_tree(glm::vec3(treeScale[i] + 0.0f));
        t_tree.add(&tr_tree);
        t_tree.add(&s_tree);
        t_tree.setTransformation(blinn);
        trees[i]->draw(VAO_tree);

        Transformation t_bush;
        Translation tr_bush(glm::vec3(treePositionX[i] + 5.0f, 0.0f, treePositionZ[i] + 5.0f));
        Scale s_bush(glm::vec3(treeScale[i] + 5.0f));
        t_bush.add(&tr_bush);
        t_bush.add(&s_bush);
        t_bush.setTransformation(blinn);
        bushes[i]->draw(VAO_bush);
    }

    texture->update();
    texture->bindTexture(texture->getTextureGrassID(), 0);

    assimp->update();
    Transformation t_grass;
    Translation tr_grass(glm::vec3(5.0f, 0.0f, 5.0f));
    Scale s_grass(glm::vec3(30.0f));
    t_grass.add(&tr_grass);
    t_grass.add(&s_grass);
    t_grass.setTransformation(assimp);
    grass.draw(VAO_plain);

    texture->update();
    assimp->update();
    Transformation t_house;
    Translation tr_house(glm::vec3(0.0f, 0.0f, 0.0f));
    Scale s_house(glm::vec3(1.0f));
    t_house.add(&tr_house);
    t_house.add(&s_house);
    t_house.setTransformation(assimp);
    modelHouse.draw();

    assimp->update();
    int fencePieceWidth = 2;
    int fenceCenterX = 5;
    int fenceCenterZ = 5;
    int fenceHalfSize = 30;

    int fenceMinX = fenceCenterX - fenceHalfSize;
    int fenceMaxX = fenceCenterX + fenceHalfSize;
    int fenceMinZ = fenceCenterZ - fenceHalfSize;
    int fenceMaxZ = fenceCenterZ + fenceHalfSize;

    int fencePiecesPerSide = (fenceMaxX - fenceMinX) / fencePieceWidth;

    for (int i = 0; i < fencePiecesPerSide; i++) {
        float x = (float)fenceMinX + (float)fencePieceWidth * 0.5f + (float)i * (float)fencePieceWidth;
        Transformation t_fence;
        Translation tr_fence(glm::vec3(x, 0.0f, (float)fenceMinZ));
        Scale s_fence(glm::vec3(1.0f));
        Rotation r_fence(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        t_fence.add(&tr_fence);
        t_fence.add(&s_fence);
        t_fence.add(&r_fence);
        t_fence.setTransformation(assimp);
        modelFence.draw();
    }

    for (int i = 0; i < fencePiecesPerSide; i++) {
        float x = (float)fenceMinX + (float)fencePieceWidth * 0.5f + (float)i * (float)fencePieceWidth;
        Transformation t_fence;
        Translation tr_fence(glm::vec3(x, 0.0f, (float)fenceMaxZ));
        Scale s_fence(glm::vec3(1.0f));
        Rotation r_fence(0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
        t_fence.add(&tr_fence);
        t_fence.add(&s_fence);
        t_fence.add(&r_fence);
        t_fence.setTransformation(assimp);
        modelFence.draw();
    }

    for (int i = 0; i < fencePiecesPerSide; i++) {
        float z = (float)fenceMinZ + (float)fencePieceWidth * 0.5f + (float)i * (float)fencePieceWidth;
        Transformation t_fence;
        Translation tr_fence(glm::vec3((float)fenceMinX, 0.0f, z));
        Scale s_fence(glm::vec3(1.0f));
        Rotation r_fence(glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        t_fence.add(&tr_fence);
        t_fence.add(&s_fence);
        t_fence.add(&r_fence);
        t_fence.setTransformation(assimp);
        modelFence.draw();
    }

    for (int i = 0; i < fencePiecesPerSide; i++) {
        float z = (float)fenceMinZ + (float)fencePieceWidth * 0.5f + (float)i * (float)fencePieceWidth;
        Transformation t_fence;
        Translation tr_fence(glm::vec3((float)fenceMaxX, 0.0f, z));
        Scale s_fence(glm::vec3(1.0f));
        Rotation r_fence(glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        t_fence.add(&tr_fence);
        t_fence.add(&s_fence);
        t_fence.add(&r_fence);
        t_fence.setTransformation(assimp);
        modelFence.draw();
    }

    for (int i = 0; i < 5; i++) {
        Transformation t_zombie;
        Translation tr_zombie(glm::vec3(zombiePositionX[i], 0.0f, zombiePositionZ[i]));
        Scale s_zombie(glm::vec3(1.5f));
        t_zombie.add(&tr_zombie);
        t_zombie.add(&s_zombie);
        t_zombie.setTransformation(assimp);
        zombies[i].draw();
    }

    for (int i = 0; i < 3; i++) {
        fireflies[i].update(deltaTime);
        glm::vec3 fireflyPosition = fireflies[i].getPosition();
        blinn->setFireflyPosition(i, fireflyPosition);
        assimp->setFireflyPosition(i, fireflyPosition);
        texture->setFireflyPosition(i, fireflyPosition);

        Transformation t_firefly;
        Translation tr_firefly(fireflyPosition);
        Scale s_firefly(glm::vec3(0.06f));
        t_firefly.add(&tr_firefly);
        t_firefly.add(&s_firefly);
        t_firefly.setTransformation(assimp);
        modelFirefly.draw();
    }
}

void Scene::drawSphereScene() {
    drawSky();

    phong->update();
    Transformation t_sphere1;
    Translation tr_sphere1(glm::vec3(-0.5f, 0.0f, 0.0f));
    Scale s_sphere1(glm::vec3(0.2f));
    t_sphere1.add(&tr_sphere1);
    t_sphere1.add(&s_sphere1);
    t_sphere1.setTransformation(phong);
    sphere1.draw(VAO_sphere);

    lambert->update();
    Transformation t_sphere2;
    Translation tr_sphere2(glm::vec3(0.5f, 0.0f, 0.0f));
    Scale s_sphere2(glm::vec3(0.2f));
    t_sphere2.add(&tr_sphere2);
    t_sphere2.add(&s_sphere2);
    t_sphere2.setTransformation(lambert);
    sphere2.draw(VAO_sphere);

    blinn->update();
    Transformation t_sphere3;
    Translation tr_sphere3(glm::vec3(0.0f, 0.5f, 0.0f));
    Scale s_sphere3(glm::vec3(0.2f));
    t_sphere3.add(&tr_sphere3);
    t_sphere3.add(&s_sphere3);
    t_sphere3.setTransformation(blinn);
    sphere3.draw(VAO_sphere);

    constant->update();
    Transformation t_sphere4;
    Translation tr_sphere4(glm::vec3(0.0f, -0.5f, 0.0f));
    Scale s_sphere4(glm::vec3(0.2f));
    t_sphere4.add(&tr_sphere4);
    t_sphere4.add(&s_sphere4);
    t_sphere4.setTransformation(constant);
    sphere4.draw(VAO_sphere);
}

void Scene::drawPlanetScene() {
    drawSky();

    texture->update();
    assimp->update();
    Transformation t_sun;
    DynamicRotation dr_sun(glm::vec3(0.0f, 1.0f, 0.0f));
    Translation tr_sun(glm::vec3(0.0f, 0.0f, 0.0f));
    Scale s_sun(glm::vec3(10.0f));
    t_sun.add(&dr_sun);
    t_sun.add(&tr_sun);
    t_sun.add(&s_sun);
    t_sun.setTransformation(assimp);
    modelSun.draw();

    texture->update();
    assimp->update();
    Transformation t_earth;
    DynamicRotation dr_earth(glm::vec3(0.0f, 1.0f, 0.0f));
    Translation tr_earth(glm::vec3(50.0f, 0.0f, 0.0f));
    Scale s_earth(glm::vec3(3.0f));
    t_earth.add(&dr_earth);
    t_earth.add(&tr_earth);
    t_earth.add(&s_earth);
    t_earth.setTransformation(assimp);
    modelEarth.draw();

    texture->update();
    assimp->update();
    double moonPositionX = 50.0f + cos(angle) * 12.0f;
    double moonPositionZ = sin(angle) * 12.0f;
    Transformation t_moon;
    DynamicRotation dr_moon(glm::vec3(0.0f, 1.0f, 0.0f));
    Translation tr_moon(glm::vec3(moonPositionX, 0.0f, moonPositionZ));
    Scale s_moon(glm::vec3(1.5f));
    t_moon.add(&dr_moon);
    t_moon.add(&tr_moon);
    t_moon.add(&s_moon);
    t_moon.setTransformation(assimp);
    modelMoon.draw();

    angle += 0.05;
    if (angle >= 2 * 3.14)
        angle -= 2 * 3.14;
}

void Scene::run(GLFWwindow* window) {
    glEnable(GL_DEPTH_TEST);
    camera.changePosition(glm::vec3(0.0f, 5.f, 50.0f));

    zombies.resize(5);
    for (int i = 0; i < 5; i++)
        zombies[i].load("models/zombie/zombie.obj");

    modelHouse.load("models/house/house.obj");
    modelFence.load("models/fence/fence.obj");
    modelFirefly.load("models/firefly/firefly.obj");
    modelSun.load("models/planet/planet.obj");
    modelEarth.load("models/planet/planet.obj");
    modelMoon.load("models/planet/planet.obj");

    assimp->useProgram();
    GLuint programID = assimp->getProgramID();

    for (int i = 0; i < 5; i++)
        zombies[i].setShaderProgram(programID);

    modelHouse.setShaderProgram(programID);
    modelFence.setShaderProgram(programID);
    modelFirefly.setShaderProgram(programID);
    modelSun.setShaderProgram(programID);
    modelEarth.setShaderProgram(programID);
    modelMoon.setShaderProgram(programID);

    modelSun.loadTexture("textures/sun.png");
    modelEarth.loadTexture("textures/earth.png");
    modelMoon.loadTexture("textures/moon.png");

    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS) {
            if (chosenScene != 0) {
                chosenScene = 0;
                camera.changePosition(glm::vec3(0.0f, 5.f, 50.0f));
            }
        } else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) {
            if (chosenScene != 1) {
                chosenScene = 1;
                camera.changePosition(glm::vec3(0.0f, 0.05f, 3.0f));
            }
        } else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) {
            if (chosenScene != 2) {
                chosenScene = 2;
                camera.changePosition(glm::vec3(0.0f, 0.05f, 50.0f));
            }
        }

        double currentFrame = glfwGetTime();
        deltaTime = (float)(currentFrame - lastFrame);
        lastFrame = (float)currentFrame;
        if (deltaTime > 0.1f) deltaTime = 0.1f;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        
        if (width > 0 && height > 0) {
            float ratio = (float)width / (float)height;
            glViewport(0, 0, width, height);
            camera.setProjectionMatrix(glm::perspective(glm::radians(45.0f), ratio, 0.1f, 100.0f));
        }

        renderScene(chosenScene);
        camera.move(window, deltaTime);
        camera.look(window, deltaTime);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}

void Scene::initialize() {
    VBO_sphere = VBO(sphere, sizeof(sphere));
    VBO_tree = VBO(tree, sizeof(tree));
    VBO_bush = VBO(bush, sizeof(bush));
    VBO_plain = VBO(plain, sizeof(plain));
    VBO_skycube = VBO(skycube, sizeof(skycube));

    VAO_sphere.bindVAO();
    VAO_sphere.linkVBO(VBO_sphere, 0);
    VBO_sphere.configure2Attributes();
    VAO_sphere.unbindVAO();

    VAO_tree.bindVAO();
    VAO_tree.linkVBO(VBO_tree, 0);
    VBO_tree.configure2Attributes();
    VAO_tree.unbindVAO();

    VAO_bush.bindVAO();
    VAO_bush.linkVBO(VBO_bush, 0);
    VBO_bush.configure2Attributes();
    VAO_bush.unbindVAO();

    VAO_plain.bindVAO();
    VAO_plain.linkVBO(VBO_plain, 0);
    VBO_plain.configure3Attributes();
    VAO_plain.unbindVAO();

    VAO_skycube.bindVAO();
    VAO_skycube.linkVBO(VBO_skycube, 0);
    VAO_skycube.unbindVAO();
}

void Scene::drawSky() {
    glDisable(GL_CULL_FACE);
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);

    cubemap->update();
    cubemap->drawSkyCube();
    cubemap->draw(VAO_skycube);

    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    glEnable(GL_CULL_FACE);
}

void Scene::createShaders() {
    shaderProgram = new ShaderProgram("shaders/vertexShader.vert", "shaders/fragmentShader.frag");
    constant = new ShaderProgram("shaders/constant.vert", "shaders/constant.frag");
    lambert = new ShaderProgram("shaders/lambert.vert", "shaders/lambert.frag");
    phong = new ShaderProgram("shaders/phong.vert", "shaders/phong.frag");
    blinn = new ShaderProgram("shaders/blinn.vert", "shaders/blinn.frag");
    texture = new ShaderProgram("shaders/texture.vert", "shaders/texture.frag");
    cubemap = new ShaderProgram("shaders/skycube.vert", "shaders/skycube.frag");
    assimp = new ShaderProgram("shaders/assimp.vert", "shaders/assimp.frag");

    texture->loadTextures();
    cubemap->loadSkyCube("textures/skybox/day");

    camera.attach(shaderProgram);
    camera.attach(constant);
    camera.attach(lambert);
    camera.attach(phong);
    camera.attach(blinn);
    camera.attach(texture);
    camera.attach(cubemap);
    camera.attach(assimp);

    shaderProgram->setCamera(&camera);
    constant->setCamera(&camera);
    lambert->setCamera(&camera);
    phong->setCamera(&camera);
    blinn->setCamera(&camera);
    texture->setCamera(&camera);
    cubemap->setCamera(&camera);
    assimp->setCamera(&camera);
}

void Scene::destroy() {
    VAO_sphere.deleteVAO();
    VAO_tree.deleteVAO();
    VAO_bush.deleteVAO();
    VAO_plain.deleteVAO();
    VAO_skycube.deleteVAO();
    VBO_sphere.deleteVBO();
    VBO_tree.deleteVBO();
    VBO_bush.deleteVBO();
    VBO_plain.deleteVBO();
    VBO_skycube.deleteVBO();

    delete shaderProgram;
    delete constant;
    delete lambert;
    delete phong;
    delete blinn;
    delete texture;
    delete cubemap;
    delete assimp;
}