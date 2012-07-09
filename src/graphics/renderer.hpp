#ifndef RENDERER_HPP_
#define RENDERER_HPP_


#include "../core/resources/mesh.hpp"
#include "../core/resources/terrain.hpp"
#include "../core/definitions.hpp"
#include "../core/resources/shader.hpp"
#include "renderedentity.hpp"

class Renderer
{
public:
	Renderer() {};
	virtual ~Renderer() {};

	// Render functions
	virtual void renderEntity(shared_ptr<RenderedEntity> entity) = 0;
	virtual void renderMesh(shared_ptr<Mesh> mesh) = 0;
	virtual void renderTerrain(shared_ptr<Terrain> terrain) = 0;

	virtual void startFrame() = 0;
	virtual void endFrame() = 0;

	// State changes
	virtual void useMaterial(shared_ptr<Material> material) = 0;
	virtual void showDebugGrid(const bool show) = 0;

	virtual void setWindowSize(const unsigned int width, const unsigned int height) = 0;

protected:
	virtual void useShader(shared_ptr<Shader> shader) = 0;
};

#endif /* RENDERER_HPP_ */
