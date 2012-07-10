#include "shader.hpp"

#include "../../utils/logger.hpp"

#include <string>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <GL/glew.h>
#include <fstream>
#include <streambuf>
#include <glm/glm.hpp>

namespace fs = boost::filesystem;
using namespace std;

Shader::Shader(fs::path basePath) :
				fragmentShader(0),
				vertexShader(0),
				programId(0),
				modelMatrixName("modelMatrix"),
				viewMatrixName("viewMatrix"),
				projectionMatrixName("projectionMatrix")

{
	//remove extension since we need two files here
	basePath.replace_extension("");
	loadFragmentShader(basePath);
	loadVertexShader(basePath);
	createProgram();
	allocateUniforms();
}

Shader::~Shader()
{
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(programId);
}

void Shader::loadFragmentShader(const fs::path& path)
{
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	fs::path newPath(path.string() + ".frag");
	loadShaderFromFile(newPath, fragmentShader);
}

void Shader::loadVertexShader(const fs::path& path)
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fs::path newPath(path.string() + ".vert");
	loadShaderFromFile(newPath, vertexShader);
}

void Shader::loadShaderFromFile(const fs::path & path, const GLuint shaderId)
{
	if (!fs::exists(path))
	{
		throw string("Shader file not found: ") + path.string();
	}

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
		Logger::error(errorMessage);
	}
}

void Shader::setModelMatrix(const glm::mat4& modelMatrix)
{
	glUniformMatrix4fv(modelMatrixId, 1, GL_FALSE, &modelMatrix[0][0]);
}

void Shader::setViewMatrix(const glm::mat4& viewMatrix)
{
	glUniformMatrix4fv(viewMatrixId, 1, GL_FALSE, &viewMatrix[0][0]);
}

void Shader::setProjectionMatrix(const glm::mat4& projectionMatrix)
{
	glUniformMatrix4fv(projectionMatrixId, 1, GL_FALSE, &projectionMatrix[0][0]);
}

void Shader::createProgram()
{
	programId = glCreateProgram();

	glAttachShader(programId, vertexShader);
	glAttachShader(programId, fragmentShader);
	glLinkProgram(programId);

	GLint result = GL_FALSE;

	glGetProgramiv(programId, GL_LINK_STATUS, &result);

	if (result != GL_TRUE)
	{
		int infoLogLength;
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
		string errorMessage;
		errorMessage.resize(infoLogLength);
		glGetProgramInfoLog(programId, infoLogLength, 0, &errorMessage[0]);
		Logger::error(errorMessage);
	}
}

void Shader::setDiffuseColor(const Color& color)
{
	glm::vec3 vecColor(color.r, color.g, color.b);
	glUniform3fv(diffuseColorId, 1, &vecColor[0]);
}

void Shader::allocateUniforms()
{
	modelMatrixId = glGetUniformLocation(programId, modelMatrixName.c_str());
	viewMatrixId = glGetUniformLocation(programId, viewMatrixName.c_str());
	projectionMatrixId = glGetUniformLocation(programId, projectionMatrixName.c_str());
	diffuseColorId = glGetUniformLocation(programId, "diffuseColor");

	//Allocate 5 lights
	for (int i = 0; i <= 5; i++)
	{
		allocateLight();
	}
}

void Shader::setLight(int index, const Light& light)
{
	glUniform3fv(lightIds[index].position, 1, &light.getPosition()[0]);
	glUniform3fv(lightIds[index].color, 1, &light.getColor()[0]);
	glUniform1f(lightIds[index].intensity, light.getIntensity());
}

int Shader::addLight(const Light& light)
{
	if (numLights < 10)
	{
		int index = numLights;
		setLight(index, light);
		numLights++;
		return index;
	}
	else
	{
		return -1;
	}
}

void Shader::clearLights()
{
}

void Shader::allocateLight()
{
	int newLightIndex = lightIds.size();
	std::string newLightGLSLName = (boost::format("lights[%d].") % newLightIndex).str();
	std::string positionName = newLightGLSLName + "position";
	std::string colorName = newLightGLSLName + "color";
	std::string intensityName = newLightGLSLName + "intensity";

	LightId newLightId;

	newLightId.position = glGetUniformLocation(programId, positionName.c_str());
	newLightId.color = glGetUniformLocation(programId, colorName.c_str());
	newLightId.intensity = glGetUniformLocation(programId, intensityName.c_str());

	lightIds.push_back(newLightId);
}

