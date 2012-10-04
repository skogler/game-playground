#include "oglrenderer.hpp"

#include "utils/logger.hpp"
#include "graphics/graphics-definitions.hpp"
#include "graphics/shaderprogram.hpp"

#include <iostream>
#include <vector>
#include <boost/format.hpp>
using namespace std;

/**
 * Load our default shader on creation.
 */
OGLRenderer::OGLRenderer(shared_ptr<ResourceManager> resourceManager, shared_ptr<Camera> camera) :
				aspectRatio(16.0f / 9.0f),
				fov(60.0f),
				camera(camera),
				debugGridEnabled(true),
				debugAxesEnabled(true),
				debugGridMaterial(resourceManager->getMaterial("debug")),
				redMaterial(resourceManager->getMaterial("debugRed")),
				blueMaterial(resourceManager->getMaterial("debugBlue")),
				greenMaterial(resourceManager->getMaterial("debugGreen")),
				colorShader(new ShaderProgram()),
				textureShader(new ShaderProgram()),
				debugShader(new ShaderProgram())

{
	debugShader->attachShader(resourceManager->getShader("defaultNoLight.vert"));
	debugShader->attachShader(resourceManager->getShader("colorNoLight.frag"));
	debugShader->addEffect(EFFECT_COLOR);
	debugShader->link();

	colorShader->attachShader(resourceManager->getShader("default.vert"));
	colorShader->attachShader(resourceManager->getShader("color.frag"));
	colorShader->addEffect(EFFECT_COLOR);
	colorShader->addEffect(EFFECT_LIGHTING);
	colorShader->link();

	textureShader->attachShader(resourceManager->getShader("default.vert"));
	textureShader->attachShader(resourceManager->getShader("texture.frag"));
	textureShader->addEffect(EFFECT_TEXTURE);
	textureShader->addEffect(EFFECT_LIGHTING);
	textureShader->link();

	updateProjectionMatrix();

	initDebugGrid();
	initDebugAxes();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
}

OGLRenderer::~OGLRenderer()
{
	glDeleteBuffers(1, &debugGridId);
	glDeleteBuffers(1, &debugAxesId);
}

void OGLRenderer::renderEntity(shared_ptr<RenderedEntity> entity)
{
	// send model matrix to shaders
	colorShader->bind();
	colorShader->setModelMatrix(entity->getModelMatrix());
	textureShader->bind();
	textureShader->setModelMatrix(entity->getModelMatrix());
	colorShader->bind();
	renderMesh(entity->getMesh());
}

void OGLRenderer::renderMesh(shared_ptr<Mesh> mesh)
{
	// index 0 => vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->getVertexBuffer());
	glVertexAttribPointer(0,                               // attribute
			3,                               // size
			GL_FLOAT,                        // type
			GL_FALSE,                        // normalized?
			0,                               // stride
			(void*) 0                         // array buffer offset
			);

	// index 1 => normals
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->getNormalBuffer());
	glVertexAttribPointer(1,                                // attribute
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*) 0                          // array buffer offset
			);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getFaceBuffer());

	// index 2 => UV Coordinates
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->getUvBuffer());
	glVertexAttribPointer(2,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*) 0                          // array buffer offset
			);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getFaceBuffer());

	vector<FaceGroup> faceGroups = mesh->getFaceGroups();
	vector<FaceGroup>::iterator iter;
	for (iter = faceGroups.begin(); iter < faceGroups.end(); ++iter)
	{
		shared_ptr<Material> mat = mesh->getMaterial(iter->materialName);
		ShaderProgram * usedShader = 0;
		if (mat->getType() == MATERIAL_TYPE_COLOR)
		{
			usedShader = colorShader.get();
		}
		else if (mat->getType() == MATERIAL_TYPE_TEXTURE)
		{
			usedShader = textureShader.get();
		}
		usedShader->bind();
		usedShader->setMaterial(*mat);

		glDrawElements(GL_TRIANGLES, iter->size, GL_UNSIGNED_INT, BUFFER_OFFSET(sizeof(unsigned int) * iter->start));
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void OGLRenderer::useMaterial(shared_ptr<Material> material)
{
	if (material->getType() == MATERIAL_TYPE_COLOR)
	{
		colorShader->setMaterial(*material);
	}
	else if (material->getType() == MATERIAL_TYPE_TEXTURE)
	{
		textureShader->setMaterial(*material);
	}

}

void OGLRenderer::enableDebugGrid(const bool show)
{
	debugGridEnabled = show;
}

void OGLRenderer::setWindowSize(const unsigned int width, const unsigned int height)
{
	aspectRatio = static_cast<float>(width / height);
	updateProjectionMatrix();
}

void OGLRenderer::startFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	colorShader->bind();
	colorShader->setViewMatrix(camera->getModelMatrix());
	textureShader->bind();
	textureShader->setViewMatrix(camera->getModelMatrix());
}

void OGLRenderer::endFrame()
{
	if (debugAxesEnabled || debugGridEnabled)
	{
		debugShader->bind();
		// draw debug stuff always in world coordinates
		debugShader->setModelMatrix(IDENTITY_MATRIX);
		debugShader->setViewMatrix(camera->getModelMatrix());
		debugShader->setProjectionMatrix(projectionMatrix);
		if (debugAxesEnabled)
		{
			drawDebugAxes();
		}
		if (debugGridEnabled)
		{
			drawDebugGrid();
		}
		colorShader->bind();
	}
}

void OGLRenderer::drawDebugGrid()
{
	debugShader->setMaterial(*debugGridMaterial);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, debugGridId);
	glVertexAttribPointer(0,                               // attribute
			3,                               // size
			GL_FLOAT,                        // type
			GL_FALSE,                        // normalized?
			0,                               // stride
			(void*) 0                         // array buffer offset
			);
	glDrawArrays(GL_LINES, 0, numDebugGridVertices);
}

void OGLRenderer::renderTerrain(shared_ptr<Terrain> terrain)
{
}

void OGLRenderer::addLight(const Light& light)
{
	colorShader->bind();
	colorShader->addLight(light);
}

void OGLRenderer::enableLighting(const bool enable)
{
	// TODO implement
}

void OGLRenderer::enableWireframe(const bool enable)
{
	if (enable)
	{
		glPolygonMode(GL_FRONT, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT, GL_FILL);
	}
}

void OGLRenderer::enableTextures(const bool enable)
{
	// TODO implement
}

void OGLRenderer::initDebugGrid()
{
	GLfloat extent = 1000.0f; // How far on the Z-Axis and X-Axis the ground extends
	GLfloat stepSize = 50.0f; // The size of the separation between points
	GLfloat groundLevel = -0.05f; // Where on the Y-Axis the ground is drawn

	std::vector<glm::vec3> debugGridVertices;
	// Draw our ground grid
	for (GLint loop = -extent; loop < extent; loop += stepSize)
	{
		// Draw lines along Z-Axis
		debugGridVertices.push_back(glm::vec3(loop, groundLevel, extent));
		debugGridVertices.push_back(glm::vec3(loop, groundLevel, -extent));

		// Draw lines across X-Axis
		debugGridVertices.push_back(glm::vec3(-extent, groundLevel, loop));
		debugGridVertices.push_back(glm::vec3(extent, groundLevel, loop));
	}

	glGenBuffers(1, &debugGridId);
	glBindBuffer(GL_ARRAY_BUFFER, debugGridId);
	glBufferData(GL_ARRAY_BUFFER, debugGridVertices.size() * sizeof(glm::vec3), &debugGridVertices[0], GL_STATIC_DRAW);
	numDebugGridVertices = debugGridVertices.size();
}

void OGLRenderer::drawDebugAxes()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, debugAxesId);
	glVertexAttribPointer(0,                               // attribute
			3,                               // size
			GL_FLOAT,                        // type
			GL_FALSE,                        // normalized?
			0,                               // stride
			(void*) 0                         // array buffer offset
			);
	debugShader->setMaterial(*redMaterial);
	glDrawArrays(GL_LINES, 0, 2);
	debugShader->setMaterial(*greenMaterial);
	glDrawArrays(GL_LINES, 2, 2);
	debugShader->setMaterial(*blueMaterial);
	glDrawArrays(GL_LINES, 4, 2);
}

void OGLRenderer::enableDebugAxes(const bool enable)
{
	debugAxesEnabled = enable;
}

void OGLRenderer::setCamera(shared_ptr<Camera> camera)
{
	this->camera = camera;
}

void OGLRenderer::initDebugAxes()
{
	std::vector<glm::vec3> debugAxesVertices;

	// X axis
	debugAxesVertices.push_back(glm::vec3(-1000.0f, 0.0f, 0.0f));
	debugAxesVertices.push_back(glm::vec3(1000.0f, 0.0f, 0.0f));

	// Y axis
	debugAxesVertices.push_back(glm::vec3(0.0f, -1000.0f, 0.0f));
	debugAxesVertices.push_back(glm::vec3(0.0f, 1000.0f, 0.0f));

	// Z axis
	debugAxesVertices.push_back(glm::vec3(0.0f, 0.0f, -1000.0f));
	debugAxesVertices.push_back(glm::vec3(0.0f, 0.0f, 1000.0f));

	glGenBuffers(1, &debugAxesId);
	glBindBuffer(GL_ARRAY_BUFFER, debugAxesId);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), &debugAxesVertices[0], GL_STATIC_DRAW);
}

