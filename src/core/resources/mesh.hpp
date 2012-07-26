#ifndef MESH_INC
#define MESH_INC

#include <vector>
#include <map>
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "core/definitions.hpp"
#include <boost/filesystem.hpp>
#include "material.hpp"

struct FaceGroup
{
	std::string materialName;
	unsigned int start;
	unsigned int size;
};

class Mesh
{
public:
	Mesh(const boost::filesystem::path & path);

	virtual ~Mesh();
	void upload();
	void release();

	const std::vector<std::string> getUsedMaterials() const;

	std::vector<unsigned int> * getFaces()
	{
		return &faces;
	}

	std::vector<glm::vec3> getNormals() const
	{
		return normals;
	}

	std::vector<glm::vec2> getUvCoordinates() const
	{
		return uvCoordinates;
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

	bool uploaded;

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

protected:
	std::map<std::string, shared_ptr<Material> > materials;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvCoordinates;
	std::vector<unsigned int> faces;
	std::vector<FaceGroup> faceGroups;
	GLuint vertexBuffer;
	GLuint faceBuffer;
	GLuint normalBuffer;
	void load(const boost::filesystem::path& path);
};

#endif /* end of include guard: MESH_INC */
