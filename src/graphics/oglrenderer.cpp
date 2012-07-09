#include "oglrenderer.hpp"

#include <vector>
using namespace std;

#include "../utils/logger.hpp"
#include <iostream>
#include "graphics-definitions.hpp"

/**
 * Load our default shader on creation.
 */
OGLRenderer::OGLRenderer(shared_ptr<ResourceManager> resourceManager, shared_ptr<Camera> camera) :
				shader(resourceManager->getShader("default")),
				aspectRatio(1.3333f),
				fov(60.0f),
				camera(camera),
				debugGridEnabled(true),
				debugMaterial(resourceManager->getMaterial("debug"))
{
	shader = resourceManager->getShader("default");
	shader->bind();
	updateProjectionMatrix();

	initDebugGrid();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
}

OGLRenderer::~OGLRenderer()
{
}

void OGLRenderer::renderEntity(shared_ptr<RenderedEntity> entity)
{
	// send model matrix to shader
	shader->setModelMatrix(entity->getModelMatrix());
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

	// index 2 => normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->getNormalBuffer());
	glVertexAttribPointer(2,                                // attribute
			3,                                // size
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
		useMaterial(mesh->getMaterial(iter->materialName));
		glDrawElements(GL_TRIANGLES, iter->size, GL_UNSIGNED_INT, BUFFER_OFFSET(sizeof(unsigned int) * iter->start));
	}
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void OGLRenderer::useMaterial(shared_ptr<Material> material)
{
	shader->setDiffuseColor(material->getDiffuse());
}

void OGLRenderer::showDebugGrid(const bool show)
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
	shader->setViewMatrix(camera->getModelMatrix());
}

void OGLRenderer::endFrame()
{
	if (debugGridEnabled)
	{
		drawDebugGrid();
	}

	int errorCode = 0;
	if (errorCode = glGetError())
	{
		std::string message = "A OpenGL error occured: " + errorCode;

		Logger::error(message);
	}
}

void OGLRenderer::useShader(shared_ptr<Shader> shader)
{
	this->shader = shader;
}

void OGLRenderer::drawDebugGrid()
{
	shader->setModelMatrix(IDENTITY_MATRIX);
	useMaterial(debugMaterial);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, debugGridId);
	glVertexAttribPointer(0,                               // attribute
			3,                               // size
			GL_FLOAT,                        // type
			GL_FALSE,                        // normalized?
			0,                               // stride
			(void*) 0                         // array buffer offset
			);
	glDrawArrays(GL_LINES, 0, debugGridVertices.size());
}

void OGLRenderer::renderTerrain(shared_ptr<Terrain> terrain)
{
}

void OGLRenderer::initDebugGrid()
{
	GLfloat extent = 1000.0f; // How far on the Z-Axis and X-Axis the ground extends
	GLfloat stepSize = 20.0f; // The size of the separation between points
	GLfloat groundLevel = -10.0f; // Where on the Y-Axis the ground is drawn

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
}

