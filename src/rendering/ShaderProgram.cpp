#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(const char* vertexShader, const char* fragmentShader)
    : ShaderLoader(vertexShader, fragmentShader, &programID),
    spotLight(sl_position, sl_direction, sl_color, constant_attenuation, linear_attenuation, quadratic_attenuation, sl_cutoff, sl_outer_cutoff),
    pointLight(pl_position, pl_color, point_constant_attenuation, point_linear_attenuation, point_quadratic_attenuation),
    directionalLight(dl_direction, dl_color),
    fireflyLight1(firefly_position, firefly_color, firefly_constant_attenuation, firefly_linear_attenuation, firefly_quadratic_attenuation),
    fireflyLight2(firefly_position, firefly_color, firefly_constant_attenuation, firefly_linear_attenuation, firefly_quadratic_attenuation),
    fireflyLight3(firefly_position, firefly_color, firefly_constant_attenuation, firefly_linear_attenuation, firefly_quadratic_attenuation),
    material1(reflection_ambient, reflection_diffuse, reflection_specular) {

    lights.push_back(&spotLight);
    lights.push_back(&pointLight);
    lights.push_back(&directionalLight);
    lights.push_back(&fireflyLight1);
    lights.push_back(&fireflyLight2);
    lights.push_back(&fireflyLight3);
    materials.push_back(&material1);

    useProgram();
    modelMatrixLoc = glGetUniformLocation(programID, "modelMatrix");
    viewMatrixLoc = glGetUniformLocation(programID, "viewMatrix");
    projectionMatrixLoc = glGetUniformLocation(programID, "projectionMatrix");
    viewPositionLoc = glGetUniformLocation(programID, "viewPosition");
    textureUnitLoc = glGetUniformLocation(programID, "textureSampler");
    skyCubeUnitLoc = glGetUniformLocation(programID, "skyCube");

    for (int i = 0; i < lights.size(); i++) {
        std::string light = "lights[" + std::to_string(i) + "]";
        lightTypeLocs.push_back(glGetUniformLocation(programID, (light + ".type").c_str()));
        lightColorLocs.push_back(glGetUniformLocation(programID, (light + ".color").c_str()));
        lightConstLocs.push_back(glGetUniformLocation(programID, (light + ".constantAttenuation").c_str()));
        lightLinearLocs.push_back(glGetUniformLocation(programID, (light + ".linearAttenuation").c_str()));
        lightQuadLocs.push_back(glGetUniformLocation(programID, (light + ".quadraticAttenuation").c_str()));
        lightPosLocs.push_back(glGetUniformLocation(programID, (light + ".position").c_str()));
        lightDirLocs.push_back(glGetUniformLocation(programID, (light + ".direction").c_str()));
        lightCutoffLocs.push_back(glGetUniformLocation(programID, (light + ".cutoff").c_str()));
        lightOuterCutoffLocs.push_back(glGetUniformLocation(programID, (light + ".outerCutoff").c_str()));
    }

    for (int i = 0; i < materials.size(); i++) {
        std::string material = "materials[" + std::to_string(i) + "]";
        materialAmbientLocs.push_back(glGetUniformLocation(programID, (material + ".ambient").c_str()));
        materialDiffuseLocs.push_back(glGetUniformLocation(programID, (material + ".diffuse").c_str()));
        materialSpecularLocs.push_back(glGetUniformLocation(programID, (material + ".specular").c_str()));
    }
}

void ShaderProgram::useProgram() const {
    glUseProgram(programID);
}

void ShaderProgram::deleteProgram() const {
    glDeleteProgram(programID);
}

void ShaderProgram::setSpotLightEnabled(bool enabled) {
    spotLightEnabled = enabled;
}

void ShaderProgram::setDirectionalLightOnly(bool enabled) {
    directionalLightOnly = enabled;
}

void ShaderProgram::setFireflyPosition(int index, const glm::vec3& position) {
    if (index == 0)
        fireflyLight1.setPosition(position);
    else if (index == 1)
        fireflyLight2.setPosition(position);
    else if (index == 2)
        fireflyLight3.setPosition(position);
}

void ShaderProgram::update() {
    useProgram();
    glm::mat4 V = camera->getViewMatrix();
    glm::mat4 P = camera->getProjectionMatrix();
    glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(V));
    glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE, glm::value_ptr(P));
    glUniform3fv(viewPositionLoc, 1, &camera->getPosition()[0]);
    sl_position = camera->getPosition();
    sl_direction = glm::normalize(camera->getFront());

    for (int i = 0; i < lights.size(); i++) {
        int type = lights[i]->getType();

        if (directionalLightOnly && type != 0)
            type = 3;
        else if (type == 2 && !spotLightEnabled)
            type = 3;

        glUniform1i(lightTypeLocs[i], type);
        glUniform3fv(lightColorLocs[i], 1, &lights[i]->getColor()[0]);
        glUniform1f(lightConstLocs[i], lights[i]->getConstantAttenuation());
        glUniform1f(lightLinearLocs[i], lights[i]->getLinearAttenuation());
        glUniform1f(lightQuadLocs[i], lights[i]->getQuadraticAttenuation());

        if (type == 2) {
            glUniform1f(lightCutoffLocs[i], lights[i]->getCutoff());
            glUniform1f(lightOuterCutoffLocs[i], lights[i]->getOuterCutoff());
            glUniform3fv(lightDirLocs[i], 1, glm::value_ptr(sl_direction));
            glUniform3fv(lightPosLocs[i], 1, glm::value_ptr(sl_position));
        } else if (type == 0) {
            glUniform3fv(lightDirLocs[i], 1, glm::value_ptr(dl_direction));
            glUniform3fv(lightPosLocs[i], 1, &lights[i]->getPosition()[0]);
        } else {
            glUniform3fv(lightDirLocs[i], 1, &lights[i]->getDirection()[0]);
            glUniform3fv(lightPosLocs[i], 1, &lights[i]->getPosition()[0]);
        }
    }

    for (int i = 0; i < materials.size(); i++) {
        glUniform1f(materialAmbientLocs[i], materials[i]->getReflectionAmbient());
        glUniform1f(materialDiffuseLocs[i], materials[i]->getReflectionDiffuse());
        glUniform1f(materialSpecularLocs[i], materials[i]->getReflectionSpecular());
    }
}

void ShaderProgram::setCamera(Camera* camera) {
    this->camera = camera;
}

void ShaderProgram::sendModelMatrix(glm::mat4& M) const {
    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(M));
}

void ShaderProgram::loadTextures() {
    if (textureGrassID == 0) {
        textureGrassID = SOIL_load_OGL_texture("textures/grass.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
        if (textureGrassID == 0) fprintf(stderr, "ERROR: Couldn't load grass.png\n");
    }

    if (textureMoonID == 0) {
        textureMoonID = SOIL_load_OGL_texture("textures/moon.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
        if (textureMoonID == 0) fprintf(stderr, "ERROR: Couldn't load moon.png\n");
    }

    if (textureSunID == 0) {
        textureSunID = SOIL_load_OGL_texture("textures/sun.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
        if (textureSunID == 0) fprintf(stderr, "ERROR: Couldn't load sun.png\n");
    }
    
    if (textureEarthID == 0) {
        textureEarthID = SOIL_load_OGL_texture("textures/earth.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
        if (textureEarthID == 0) fprintf(stderr, "ERROR: Couldn't load earth.png\n");
    }
}

void ShaderProgram::bindTexture(GLuint textureId, int textureUnit) const {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glUniform1i(textureUnitLoc, textureUnit);
}

void ShaderProgram::loadSkyCube(const std::string& folderPath) {
    if (cubemapID != 0) {
        glDeleteTextures(1, &cubemapID);
        cubemapID = 0;
    }

    std::vector faces = {
        folderPath + "/posx.jpg",
        folderPath + "/negx.jpg",
        folderPath + "/posy.jpg",
        folderPath + "/negy.jpg",
        folderPath + "/posz.jpg",
        folderPath + "/negz.jpg"
    };

    glActiveTexture(GL_TEXTURE2);
    cubemapID = SOIL_load_OGL_cubemap(
        faces[0].c_str(),
        faces[1].c_str(),
        faces[2].c_str(),
        faces[3].c_str(),
        faces[4].c_str(),
        faces[5].c_str(),
        SOIL_LOAD_RGB,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS
    );

    if (cubemapID == 0) {
        fprintf(stderr, "ERROR: Couldn't load skybox from folder: %s\n", folderPath.c_str());
        return;
    }

    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    skyFolder = folderPath;
}

void ShaderProgram::switchSkyCube(const std::string& folderPath) {
    if (folderPath == skyFolder) return;
    loadSkyCube(folderPath);
}

void ShaderProgram::drawSkyCube() const {
    if (cubemapID == 0) {
        fprintf(stderr, "ERROR: Couldn't load skybox\n");
        return;
    }

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID);
    glUniform1i(skyCubeUnitLoc, 2);
}

void ShaderProgram::draw(VAO& VAO) {
    skyCube.draw(VAO);
}

GLuint ShaderProgram::getProgramID() const {
    return programID;
}

GLuint ShaderProgram::getTextureGrassID() const {
    return textureGrassID;
}

ShaderProgram::~ShaderProgram() {
    if (camera)
        camera->detach(this);

    deleteShader();
}