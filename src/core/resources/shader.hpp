#ifndef SHADER_HPP_
#define SHADER_HPP_

#include <string>
#include <boost/filesystem.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "material.hpp"
#include "../../graphics/light.hpp"

struct LightId
{
	GLuint position;
	GLuint color;
	GLuint intensity;
};

class Shader
{
public:
	Shader(boost::filesystem::path basePath);
	virtual ~Shader();

	/**
	 * Binds the shader program so all following render
	 * operations are handled by it.
	 */
	inline void bind() const { glUseProgram(programId); }
	/**
	 * Returns the identifier that is used to access the
	 * shader program on the graphics card.
	 */
	inline GLuint getId() const { return programId; }

	void setModelMatrix(const glm::mat4& modelMatrix);
	void setViewMatrix(const glm::mat4& viewMatrix);
	void setProjectionMatrix(const glm::mat4& projectionMatrix);
	void setDiffuseColor(const Color& color);

	/**
	 * Sets the light source at the specified index.
	 */
	void setLight(int index, const Light & light);
	/**
	 * Adds a light to the list of light sources and returns
	 * its inserted index
	 */
	int addLight(const Light & light);
	/**
	 * Removes all light sources.
	 */
	void clearLights();

protected:
	std::string modelMatrixName;
	std::string viewMatrixName;
	std::string projectionMatrixName;

	GLuint programId;
	GLuint vertexShader;
	GLuint fragmentShader;

	GLuint modelMatrixId;
	GLuint viewMatrixId;
	GLuint projectionMatrixId;

	GLuint diffuseColorId;

	std::vector<LightId> lightIds;
	unsigned int numLights;

	void loadFragmentShader(const boost::filesystem::path& basePath);
	void loadVertexShader(const boost::filesystem::path& basePath);
	void loadShaderFromFile(const boost::filesystem::path& path, GLuint shaderId);
	void createProgram();

	void allocateUniforms();
	void allocateLight();
};

#endif /* SHADER_HPP_ */
