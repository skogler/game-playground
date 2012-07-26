#include "shaderprogram.hpp"

#include "utils/logger.hpp"

#include <glm/glm.hpp>
#include <GL/glew.h>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <string>
#include <fstream>
#include <streambuf>

#include "core/resources/shader.hpp"

namespace fs = boost::filesystem;
using namespace std;

ShaderProgram::ShaderProgram() :
				modelMatrixName("modelMatrix"),
				viewMatrixName("viewMatrix"),
				projectionMatrixName("projectionMatrix"),
				numLights(0),
				programId(glCreateProgram())
{
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(programId);
}

void ShaderProgram::setModelMatrix(const glm::mat4& modelMatrix)
{
	glUniformMatrix4fv(modelMatrixId, 1, GL_FALSE, &modelMatrix[0][0]);
}

void ShaderProgram::setViewMatrix(const glm::mat4& viewMatrix)
{
	glUniformMatrix4fv(viewMatrixId, 1, GL_FALSE, &viewMatrix[0][0]);
}

void ShaderProgram::setProjectionMatrix(const glm::mat4& projectionMatrix)
{
	glUniformMatrix4fv(projectionMatrixId, 1, GL_FALSE, &projectionMatrix[0][0]);
}

void ShaderProgram::setMaterial(const Material& material)
{
	if (material.getType() == MATERIAL_TYPE_TEXTURE)
	{

	}
	else
	{
		glUniform4f(materialId.diffuseColor, material.getDiffuse().r, material.getDiffuse().g, material.getDiffuse().b,
				material.getDiffuse().intensity);
		glUniform4f(materialId.specularColor, material.getSpecular().r, material.getSpecular().g, material.getSpecular().b,
				material.getSpecular().intensity);
		glUniform1f(materialId.ambient, 1.0f); // TODO use real value
	}

}

void ShaderProgram::allocateUniforms()
{
	modelMatrixId = glGetUniformLocation(programId, modelMatrixName.c_str());
	viewMatrixId = glGetUniformLocation(programId, viewMatrixName.c_str());
	projectionMatrixId = glGetUniformLocation(programId, projectionMatrixName.c_str());

	materialId.diffuseColor = glGetUniformLocation(programId, "material.diffuseColor");
	materialId.specularColor = glGetUniformLocation(programId, "material.specularColor");
	materialId.ambient = glGetUniformLocation(programId, "material.ambient");

	// If this shader can do lighting, allocate the uniforms for it
	if (hasEffect(EFFECT_LIGHTING))
	{
		//Allocate 5 lights
		for (int i = 0; i <= 5; i++)
		{
			allocateLight();
		}
	}
}

void ShaderProgram::setLight(int index, const Light& light)
{
	glUniform3fv(lightIds[index].position, 1, &light.getPosition()[0]);
	glUniform3fv(lightIds[index].color, 1, &light.getColor()[0]);
	glUniform1f(lightIds[index].intensity, light.getIntensity());
	glUniform1f(lightIds[index].linearAttenuation, light.getLinearAttenuation());
	glUniform1f(lightIds[index].squaredAttenuation, light.getSquaredAttenuation());
}

int ShaderProgram::addLight(const Light& light)
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

void ShaderProgram::clearLights()
{
}

void ShaderProgram::attachShader(shared_ptr<Shader> shader)
{
	shaders.push_back(shader);
	glAttachShader(programId, shader->getShaderId());
}

void ShaderProgram::link()
{
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
		throw std::runtime_error("Shader program failed to link: " + errorMessage);
	}
	allocateUniforms();
}

bool ShaderProgram::hasEffect(const Effect effect)
{
	return find(effects.begin(), effects.end(), effect) != effects.end();
}

void ShaderProgram::addEffect(const Effect effect)
{
	effects.push_back(effect);
}

void ShaderProgram::allocateLight()
{
	int newLightIndex = lightIds.size();
	std::string newLightGLSLName = (boost::format("lights[%d].") % newLightIndex).str();
	std::string positionName = newLightGLSLName + "position";
	std::string colorName = newLightGLSLName + "color";
	std::string intensityName = newLightGLSLName + "intensity";
	std::string linearAttenuationName = newLightGLSLName + "linearAttenuation";
	std::string squaredAttenuationName = newLightGLSLName + "squaredAttenuation";

	LightId newLightId;

	newLightId.position = glGetUniformLocation(programId, positionName.c_str());
	newLightId.color = glGetUniformLocation(programId, colorName.c_str());
	newLightId.intensity = glGetUniformLocation(programId, intensityName.c_str());
	newLightId.linearAttenuation = glGetUniformLocation(programId, linearAttenuationName.c_str());
	newLightId.squaredAttenuation = glGetUniformLocation(programId, squaredAttenuationName.c_str());

	lightIds.push_back(newLightId);
}

