#pragma once
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include "core/Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include "ShaderLoader.h"
#include "patterns/Observer.h"
#include "lights/PointLight.h"
#include "lights/SpotLight.h"
#include "lights/DirectionalLight.h"
#include "objects/SkyCube.h"
#include "stb_image.h"
#include "rendering/Material.h"
#include <vector>
#include "SOIL.h"
#include "lights/Light.h"

#define STB_IMAGE_IMPLEMENTATION

class Camera;

class ShaderProgram : public ShaderLoader, public Observer
{
private:
    GLuint programID;
    Camera* camera;
    SkyCube skyCube;
    std::vector<Light*> lights;
    std::vector<Material*> materials;
    GLuint textureGrassID = 0;
    GLuint textureMoonID = 0;
    GLuint textureSunID = 0;
    GLuint textureEarthID = 0;
    GLuint cubemapID = 0;
    bool spotLightEnabled = true;
    bool directionalLightOnly = false;
    std::string skyFolder = "textures/skybox/day";

    glm::vec3 pl_position = glm::vec3(-18.0f, 2.5f, -18.0f);
    glm::vec3 pl_color = glm::vec3(1.0f, 0.15f, 0.1f);

    glm::vec3 sl_position;
    glm::vec3 sl_direction;
    glm::vec3 sl_color = glm::vec3(1.0f, 1.0f, 0.0f);
    float sl_cutoff = cos(glm::radians(12.5f));
    float sl_outer_cutoff = cos(glm::radians(15.0f));

    glm::vec3 dl_direction = glm::vec3(-1.0f, -0.5f, 0.0f);
    glm::vec3 dl_color = glm::vec3(0.4f, 0.5f, 1.0f);

    float point_constant_attenuation = 1.0f;
    float point_linear_attenuation = 0.22f;
    float point_quadratic_attenuation = 0.20f;

    float constant_attenuation = 1.0f;
    float linear_attenuation = 0.09f;
    float quadratic_attenuation = 0.032f;

    glm::vec3 firefly_position = glm::vec3(0.0f);
    glm::vec3 firefly_color = glm::vec3(1.0f, 0.9f, 0.3f);
    float firefly_constant_attenuation = 1.0f;
    float firefly_linear_attenuation = 0.05f;
    float firefly_quadratic_attenuation = 0.01f;

    float reflection_ambient = 1.0f;
    float reflection_diffuse = 1.0f;
    float reflection_specular = 1.0f;

    SpotLight spotLight;
    PointLight pointLight;
    DirectionalLight directionalLight;
    PointLight fireflyLight1, fireflyLight2, fireflyLight3;
    Material material1;

    GLuint modelMatrixLoc, viewMatrixLoc, projectionMatrixLoc, viewPositionLoc, textureUnitLoc, skyCubeUnitLoc;
    std::vector<GLuint> lightTypeLocs, lightColorLocs, lightConstLocs, lightLinearLocs, lightQuadLocs, lightPosLocs, lightDirLocs, lightCutoffLocs, lightOuterCutoffLocs;
    std::vector<GLuint> materialAmbientLocs, materialDiffuseLocs, materialSpecularLocs;

public:
    ShaderProgram(const char* vertexShader, const char* fragmentShader);
    void useProgram() const;
    void deleteProgram() const;
    void update() override;
    void setCamera(Camera* camera);
    void setSpotLightEnabled(bool enabled);
    void setDirectionalLightOnly(bool enabled);
    void setFireflyPosition(int index, const glm::vec3& position);
    void sendModelMatrix(glm::mat4& M) const;
    void loadTextures();
    void bindTexture(GLuint textureId, int textureUnit) const;
    void loadSkyCube(const std::string& folderPath);
    void switchSkyCube(const std::string& folderPath);
    void drawSkyCube() const;
    void draw(VAO& VAO);
    GLuint getProgramID() const;
    GLuint getTextureGrassID() const;
    ~ShaderProgram() override;
};