#ifndef SHADER_HPP_
#define SHADER_HPP_

#include <string>
#include <boost/filesystem.hpp>
#include <GL/glew.h>

class Shader
{
public:
	Shader(const std::string& vertexShaderName, const std::string& fragmentShaderName);
	virtual ~Shader();

	inline void bind() const { glUseProgram(program); }
	inline GLuint get_id() const { return program; }

	inline static void setSearchDirectory(const std::string& searchDirectory) { Shader::searchDirectory = searchDirectory; }

protected:
	GLuint program;
	GLuint vertexShader;
	GLuint fragmentShader;

	void loadFragmentShader(const std::string& name);
	void loadVertexShader(const std::string& name);
	void loadShaderFromFile(const boost::filesystem::path& path, GLuint shaderId);
	void createProgram();

private:
	static boost::filesystem::path searchDirectory;
};

#endif /* SHADER_HPP_ */
