#ifndef OGLRENDERER_HPP_
#define OGLRENDERER_HPP_

#include "renderer.hpp"
#include "camera.hpp"
#include "../core/resourcemanager.hpp"
#include "../core/definitions.hpp"

class OGLRenderer: public Renderer
{
public:
	// We need a resource manager instance to load our shader(-s)
	OGLRenderer(shared_ptr<ResourceManager> resourceManager, shared_ptr<Camera> camera);
	virtual ~OGLRenderer();

	// Render functions
	virtual void renderEntity(shared_ptr<RenderedEntity> entity);
	virtual void renderMesh(shared_ptr<Mesh> mesh);
	virtual void renderTerrain(shared_ptr<Terrain> terrain);

	virtual void startFrame();
	virtual void endFrame();

	// State changes
	virtual void useMaterial(shared_ptr<Material> material);
	virtual void showDebugGrid(const bool show);

	virtual void setWindowSize(const unsigned int width, const unsigned int height);

protected:
	virtual void useShader(shared_ptr<Shader> shader);

	void drawDebugGrid();
	void initDebugGrid();

	inline void updateProjectionMatrix()
	{
		projectionMatrix = glm::perspective(fov, aspectRatio, 0.1f, 1000.0f);
		// send it to the shader
		shader->setProjectionMatrix(projectionMatrix);
	}

	shared_ptr<Shader> shader;
	shared_ptr<Camera> camera;

	glm::mat4 projectionMatrix;

	float aspectRatio;
	float fov;

	bool debugGridEnabled;
	std::vector< glm::vec3 > debugGridVertices;
	GLuint debugGridId;
	shared_ptr<Material> debugMaterial;
};

#endif /* OGLRENDERER_HPP_ */
