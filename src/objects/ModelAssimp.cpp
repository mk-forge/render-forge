#include "objects/ModelAssimp.h"

void ModelAssimp::load(const std::string& fileName) {
    Assimp::Importer importer;
    unsigned int importOptions = aiProcess_Triangulate
        | aiProcess_OptimizeMeshes
        | aiProcess_JoinIdenticalVertices
        | aiProcess_CalcTangentSpace;

    const aiScene* scene = importer.ReadFile(fileName, importOptions);

    if (scene) {
        std::string directory;
        size_t slashPos = fileName.find_last_of('/');
        if (slashPos != std::string::npos) directory = fileName.substr(0, slashPos + 1);

        std::vector<GLuint> materialTextures(scene->mNumMaterials, 0);
        for (unsigned int m = 0; m < scene->mNumMaterials; m++) {
            const aiMaterial* material = scene->mMaterials[m];
            if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
                aiString texPath;
                material->GetTexture(aiTextureType_DIFFUSE, 0, &texPath);
                std::string fullPath = directory + texPath.C_Str();
                GLuint texID = SOIL_load_OGL_texture(fullPath.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
                if (texID == 0) fprintf(stderr, "ERROR: Couldn't load texture %s\n", fullPath.c_str());
                materialTextures[m] = texID;
            }
        }

        for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
            aiMesh const* mesh = scene->mMeshes[i];
            std::vector<Vertex> vertices(mesh->mNumVertices);

            for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
                if (mesh->HasPositions()) {
                    vertices[j].Position[0] = mesh->mVertices[j].x;
                    vertices[j].Position[1] = mesh->mVertices[j].y;
                    vertices[j].Position[2] = mesh->mVertices[j].z;
                }
                
                if (mesh->HasNormals()) {
                    vertices[j].Normal[0] = mesh->mNormals[j].x;
                    vertices[j].Normal[1] = mesh->mNormals[j].y;
                    vertices[j].Normal[2] = mesh->mNormals[j].z;
                }
                
                if (mesh->HasTextureCoords(0)) {
                    vertices[j].Texture[0] = mesh->mTextureCoords[0][j].x;
                    vertices[j].Texture[1] = mesh->mTextureCoords[0][j].y;
                }

                if (mesh->HasTangentsAndBitangents()) {
                    vertices[j].Tangent[0] = mesh->mTangents[j].x;
                    vertices[j].Tangent[1] = mesh->mTangents[j].y;
                    vertices[j].Tangent[2] = mesh->mTangents[j].z;
                }
            }

            std::vector<unsigned int> indices;
            if (mesh->HasFaces()) {
                indices.resize((size_t)mesh->mNumFaces * 3);

                for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
                    indices[(size_t)j * 3] = mesh->mFaces[j].mIndices[0];
                    indices[(size_t)j * 3 + 1] = mesh->mFaces[j].mIndices[1];
                    indices[(size_t)j * 3 + 2] = mesh->mFaces[j].mIndices[2];
                }
            }

            Mesh newMesh{};
            newMesh.textureID = materialTextures[mesh->mMaterialIndex];

            glGenVertexArrays(1, &newMesh.VAO);
            glGenBuffers(1, &newMesh.VBO);
            glGenBuffers(1, &newMesh.IBO);

            glBindVertexArray(newMesh.VAO);
            glBindBuffer(GL_ARRAY_BUFFER, newMesh.VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)nullptr);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(GLfloat)));

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newMesh.IBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);

            newMesh.indicesCount = mesh->mNumFaces * 3;

            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);

            meshes.push_back(newMesh);
        }
    } else {
        fprintf(stderr, "ERROR: Failed to parse mesh from %s: %s\n", fileName.c_str(), importer.GetErrorString());
    }

    glBindVertexArray(0);
}

void ModelAssimp::loadTexture(const std::string& filename) {
    if (textureLoaded) return;

    glActiveTexture(GL_TEXTURE0);
    this->textureID = SOIL_load_OGL_texture(filename.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
    this->textureLoaded = true;
}

void ModelAssimp::draw() const {
    for (const Mesh& mesh : meshes) {
        GLuint texToBind = (mesh.textureID != 0) ? mesh.textureID : textureID;

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texToBind);
        GLint loc = glGetUniformLocation(shaderProgramID, "textureSampler");
        glUniform1i(loc, 0);

        glBindVertexArray(mesh.VAO);
        glDrawElements(GL_TRIANGLES, mesh.indicesCount, GL_UNSIGNED_INT, nullptr);
        glBindVertexArray(0);
    }
}

void ModelAssimp::setShaderProgram(GLuint programID) {
    this->shaderProgramID = programID;
}