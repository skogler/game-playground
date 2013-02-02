#ifndef MESH_INC
#define MESH_INC

#include <vector>
#include <map>
#include <string>
#include <cstdint>

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <boost/filesystem.hpp>

#include "core/definitions.hpp"
#include "material.hpp"

struct M42Header
{
  std::uint32_t numVertices;
  std::uint32_t numFaces;
  std::uint32_t numFaceGroups;
};

struct M42Vertex
{
  float position[3];
  float normal[3];
  float textureCoordinates[2]; // UV coordinates
};

struct FaceGroup
{
  std::string materialName;
  std::uint32_t start;
  std::uint32_t size;
};

class Mesh
{
  protected:
    bool uploaded;
    std::map<std::string, shared_ptr<Material> > materials;
    // Vertex data
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textureCoordinates;
    std::vector<GLuint> faces;
    std::vector<FaceGroup> faceGroups;

    GLuint vertexBuffer;
    GLuint faceBuffer;
    GLuint normalBuffer;
    GLuint uvBuffer;
    void load(const boost::filesystem::path& path);

  public:
    Mesh(const boost::filesystem::path & path);

    virtual ~Mesh();
    void upload();
    void release();

    const std::vector<std::string> getUsedMaterials() const;

    GLuint getUvBuffer() const
    {
      return uvBuffer;
    }

    void setUvBuffer(GLuint uvBuffer)
    {
      this->uvBuffer = uvBuffer;
    }

    std::vector<GLuint> * getFaces()
    {
      return &faces;
    }

    std::vector<glm::vec3> getNormals() const
    {
      return normals;
    }

    std::vector<glm::vec2> getUvCoordinates() const
    {
      return textureCoordinates;
    }

    std::vector<glm::vec3> getVertices() const
    {
      return vertices;
    }

    GLuint getFaceBuffer() const
    {
      return faceBuffer;
    }

    GLuint getNormalBuffer() const
    {
      return normalBuffer;
    }

    GLuint getVertexBuffer() const
    {
      return vertexBuffer;
    }

    inline std::vector<FaceGroup>& getFaceGroups()
    {
      return faceGroups;
    }

    inline bool isUploaded() const
    {
      return uploaded;
    }

    inline void setMaterial(const std::string& name, shared_ptr<Material> material)
    {
      materials[name] = material;
    }

    inline shared_ptr<Material> getMaterial(const std::string& name)
    {
      return materials[name];
    }

};

#endif /* end of include guard: MESH_INC */
