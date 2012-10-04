#include "shader.hpp"

#include <string>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <GL/glew.h>
#include <fstream>
#include <streambuf>

#include "utils/logger.hpp"
namespace fs = boost::filesystem;
using namespace std;

Shader::Shader(const boost::filesystem::path& filepath)
{
	GLuint shaderType = GL_VERTEX_SHADER;
	string extension = filepath.extension().string();
	if(extension == ".vert")
	{
		type = VERTEX;
		shaderType = GL_VERTEX_SHADER;
	}
	else if (extension == ".frag")
	{
		type = FRAGMENT;
		shaderType = GL_FRAGMENT_SHADER;
	}
	else if (extension == ".geom")
	{
		type = GEOMETRY;
		shaderType = GL_GEOMETRY_SHADER;
	}
	shaderId = glCreateShader(shaderType);
	if(shaderId == 0)
	{
		throw new std::runtime_error((boost::format("Shader allocation failed, shader type was: %d")  %  shaderType).str());
	}
	loadFromFile(filepath);
}

Shader::~Shader()
{
	glDeleteShader(shaderId);
}

void Shader::loadFromFile(const fs::path & path)
{
	string shaderCode;
	ifstream file(path.c_str(), ios::in);
	if (file.good())
	{
		shaderCode = string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	}

	Logger::debug(string("Compiling shader: ") + path.string());
	char const * pShaderCode = shaderCode.c_str();
	glShaderSource(shaderId, 1, &pShaderCode, 0);
	glCompileShader(shaderId);

	GLint result = GL_FALSE;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

	if (result != GL_TRUE)
	{
		int infoLogLength;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
		string errorMessage;
		errorMessage.resize(infoLogLength);
		glGetShaderInfoLog(shaderId, infoLogLength, 0, &errorMessage[0]);
		errorMessage = "Compiling shader " + path.string() + " failed: \n" + errorMessage;
		Logger::error(errorMessage);
		throw std::runtime_error(errorMessage);
	}
}
