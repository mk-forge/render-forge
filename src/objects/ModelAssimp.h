#pragma once
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <array>
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "rendering/ShaderProgram.h"

struct Vertex {
    std::array<float, 3> Position;
    std::array<float, 3> Normal;
    std::array<float, 2> Texture;
    std::array<float, 3> Tangent;
};

struct Mesh {
    GLuint VAO, VBO, IBO;
    GLuint indicesCount;
    GLuint textureID = 0;
};

class ModelAssimp
{
private:
    std::vector<Mesh> meshes;
    GLuint textureID = 0;
    GLuint shaderProgramID = 0;
    bool textureLoaded = false;

public:
    void load(const std::string& fileName);
    void loadTexture(const std::string& filename);
    void draw() const;
    void setShaderProgram(GLuint programID);
};