#ifndef MESH_INC
#define MESH_INC

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>

class Mesh
{
public:
	Mesh(const std::string& filename);

	virtual ~Mesh();
	void upload();
	void release();
	void render();

    bool uploaded;
    GLuint vbo;
    GLuint indexVbo;

    inline bool isUploaded() const
	{
		return uploaded;
	}
protected:
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> faces;

	GLuint vertexBuffer;
	GLuint faceBuffer;
	GLuint normalBuffer;

	void load(const std::string& filename);
};

#endif /* end of include guard: MESH_INC */
