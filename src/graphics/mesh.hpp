#ifndef MESH_INC
#define MESH_INC

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <GL/gl.h>

class Mesh
{
public:
    Mesh (std::string &filename);
    virtual ~Mesh ();
    void upload();
    void release();
    void draw();

    inline bool isUploaded() const { return uploaded; }
protected:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<int> faces;

    bool uploaded;
    GLuint vboId;
    GLuint indexVboId;

    void load(std::string& filename);

};

#endif /* end of include guard: MESH_INC */
