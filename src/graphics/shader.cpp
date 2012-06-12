#include "shader.hpp"

#include "../utils/logger.hpp"

#include <fstream>
#include <streambuf>

namespace fs = boost::filesystem;
using namespace std;

fs::path Shader::searchDirectory = "resources/shaders";

Shader::Shader(const string& vertexShaderName, const string& fragmentShaderName) :
		fragmentShader(0),
		vertexShader(0),
		program(0)
{
	loadFragmentShader(fragmentShaderName);
	loadVertexShader(vertexShaderName);
	createProgram();
}

Shader::~Shader()
{
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(program);
}

void Shader::loadFragmentShader(const string & name)
{
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	fs::path filename(name + string(".frag"));
	loadShaderFromFile(filename, fragmentShader);
}

void Shader::loadVertexShader(const string & name)
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fs::path filename(name + string(".vert"));
	loadShaderFromFile(filename, vertexShader);
}

void Shader::loadShaderFromFile(const fs::path & filename, const GLuint shaderId)
{
	fs::path full_path = searchDirectory / filename;
	if (!fs::exists(full_path))
	{
		throw string("Shader file not found: ") + filename.string();
	}

	string shaderCode;
	ifstream file(full_path.string().c_str(), ios::in);
	if (file.good())
	{
		shaderCode = string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	}

	Logger::debug(string("Compiling shader: ") + filename.string());
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
		Logger::error(errorMessage);
	}
}

void Shader::createProgram()
{
	program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	GLint result = GL_FALSE;

	glGetProgramiv(program, GL_LINK_STATUS, &result);

	if (result != GL_TRUE)
	{
		int infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		string errorMessage;
		errorMessage.resize(infoLogLength);
		glGetProgramInfoLog(program, infoLogLength, 0, &errorMessage[0]);
		Logger::error(errorMessage);
	}
}
