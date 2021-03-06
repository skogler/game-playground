#include "mesh.hpp"

#include "exceptions/invalidresourceerror.hpp"
#include "utils/logger.hpp"

#include <GL/glew.h>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include <boost/format.hpp>

#define FAIL_MATERIAL "fail"


#define MSG_LOADED_MODEL "Loaded model: "
#define MSG_INVALID_M42_FILE "Model file is not a valid M42 file"
#define MSG_CANNOT_OPEN_FILE "Could not open file"

static const char M42_MAGIC[] =
{
    '\x42', 'M', '4', '2', '\r', '\n', '\032', '\n'
};


#include <iostream>

using namespace std;
using boost::lexical_cast;

Mesh::Mesh(const boost::filesystem::path& path) :
    uploaded(false),
    vertexBuffer(0),
    faceBuffer(0),
    normalBuffer(0),
    uvBuffer(0),
    vertexArrayObject(0)
{
    load(path);
    Logger::debug(string(MSG_LOADED_MODEL) + path.string());
}

Mesh::~Mesh()
{
    if (uploaded)
    {
        release();
    }
}

void Mesh::upload()
{
    glGenVertexArrays(1, &vertexArrayObject);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindVertexArray(vertexArrayObject);

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3),
                 &vertices[0], GL_STATIC_DRAW);
    // index 0 => vertices
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,        // attribute
                          3,        // size
                          GL_FLOAT, // type
                          GL_FALSE, // normalized?
                          0,        // stride
                          (void*) 0 // array
                                    // buffer
                                    // offset
                         );

    glGenBuffers(1, &normalBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3),
                 &normals[0], GL_STATIC_DRAW);
    // index 1 => normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,        // attribute
                          3,        // size
                          GL_FLOAT, // type
                          GL_FALSE, // normalized?
                          0,        // stride
                          (void*) 0 // array
                                    // buffer
                                    // offset
                         );


    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, textureCoordinates.size() * sizeof(glm::vec2),
                 &textureCoordinates[0], GL_STATIC_DRAW);


    // index 2 => UV Coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,        // attribute
                          2,        // size
                          GL_FLOAT, // type
                          GL_FALSE, // normalized?
                          0,        // stride
                          (void*) 0 // array
                                    // buffer
                                    // offset
                         );

    glGenBuffers(1, &faceBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faceBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * 3 * sizeof(GLuint),
                 &faces[0], GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Mesh::release()
{
    glDeleteVertexArrays(1, &vertexArrayObject);
    vertexArrayObject = 0;
    glDeleteBuffers(1, &vertexBuffer);
    vertexBuffer = 0;
    glDeleteBuffers(1, &faceBuffer);
    faceBuffer = 0;
    glDeleteBuffers(1, &normalBuffer);
    normalBuffer = 0;
    glDeleteBuffers(1, &uvBuffer);
    uvBuffer = 0;
}

const std::vector<std::string> Mesh::getUsedMaterials() const
{
    vector<string> usedMaterials;
    for (vector<FaceGroup>::const_iterator iter = faceGroups.begin();
         iter != faceGroups.end(); ++iter)
    {
        usedMaterials.push_back(iter->materialName);
    }
    return usedMaterials;
}

void Mesh::load(const boost::filesystem::path& path)
{
    // This method assumes little-endian system
    // should be no problem since our machines are all little endian
    ifstream file(path.c_str(), std::ios::binary);

    // file.exceptions(ifstream::failbit | ifstream::badbit | ifstream::eofbit);
    file.exceptions(ifstream::eofbit);
    if (!file.good())
    {
        throw InvalidResourceError(path.string(), string(MSG_CANNOT_OPEN_FILE));
    }
    char magicHeader[sizeof(M42_MAGIC)];
    file.read(magicHeader, sizeof(magicHeader));
    if (strncmp(M42_MAGIC, magicHeader, sizeof(M42_MAGIC)))
    {
        throw InvalidResourceError(path.string(),
                                   string(MSG_INVALID_M42_FILE));
    }
    uint8_t version = 0;
    file.read((char*) &version, sizeof(version));
    if (version != 1)
    {
        throw InvalidResourceError(path.string(),
                                   string(MSG_INVALID_M42_FILE));
    }
    uint8_t numMeshes = 0;
    file.read((char*) &numMeshes, 1);
    for (uint8_t mesh_index = 0; mesh_index < numMeshes; ++mesh_index)
    {
        uint32_t numVertices;
        uint32_t numFaces;
        uint32_t numFaceGroups;

        file.read((char*) &numVertices, sizeof(numVertices));
        file.read((char*) &numFaces, sizeof(numFaces));
        file.read((char*) &numFaceGroups, sizeof(numFaceGroups));

        for (uint32_t i = 0; i < numVertices; ++i)
        {
            glm::vec3 position(0.0f);
            glm::vec3 normal(0.0f);
            glm::vec2 uv(0.0f);
            file.read((char*) &position, sizeof(position));
            file.read((char*) &normal, sizeof(normal));
            file.read((char*) &uv, sizeof(uv));
            vertices.push_back(position);
            normals.push_back(normal);
            textureCoordinates.push_back(uv);
        }
        for (uint32_t i = 0; i < (numFaces * 3); ++i)
        {
            uint32_t vertex_index = 0;
            file.read((char*) &vertex_index, sizeof(vertex_index));
            faces.push_back((GLuint) vertex_index);
        }
        for (uint32_t i = 0; i < numFaceGroups; ++i)
        {
            uint8_t   materialNameLength = 0;
            FaceGroup fg;
            file.read((char*) &materialNameLength, sizeof(materialNameLength));
            char* buffer = (char*) malloc(materialNameLength + 2);
            file.get(buffer, materialNameLength + 1);
            fg.materialName = string(buffer);
            free(buffer);
            buffer = NULL;
            file.read((char*) &(fg.start), sizeof(fg.start));
            file.read((char*) &(fg.size), sizeof(fg.size));
            faceGroups.push_back(fg);
        }
        file.close();
    }
}
