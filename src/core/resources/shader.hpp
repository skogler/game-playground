#ifndef SHADER_HPP_
#define SHADER_HPP_

#include <string>
#include <boost/filesystem.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "material.hpp"

class Shader
{
public:
	Shader(boost::filesystem::path basePath);
	virtual ~Shader();

	inline void bind() const { glUseProgram(program); }
	inline GLuint get_id() const { return program; }

	void setModelMatrix(const glm::mat4& modelMatrix);
	void setViewMatrix(const glm::mat4& viewMatrix);
	void setProjectionMatrix(const glm::mat4& projectionMatrix);
	void setDiffuseColor(const Color& color);

protected:
	std::string modelMatrixName;
	std::string viewMatrixName;
	std::string projectionMatrixName;

	GLuint program;
	GLuint vertexShader;
	GLuint fragmentShader;


	GLuint modelMatrixId;
	GLuint viewMatrixId;
	GLuint projectionMatrixId;

	GLuint diffuseColorId;

	void loadFragmentShader(const boost::filesystem::path& basePath);
	void loadVertexShader(const boost::filesystem::path& basePath);
	void loadShaderFromFile(const boost::filesystem::path& path, GLuint shaderId);
	void createProgram();

	void allocateMatriceIds();
};

#endif /* SHADER_HPP_ */
