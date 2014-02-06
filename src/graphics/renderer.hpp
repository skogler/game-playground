#ifndef RENDERER_HPP_
#define RENDERER_HPP_


#include "core/resources/mesh.hpp"
#include "core/resources/terrain.hpp"
#include "core/definitions.hpp"
#include "core/resources/shader.hpp"
#include "graphics/shaderprogram.hpp"
#include "graphics/camera.hpp"
#include "renderedentity.hpp"
#include "light.hpp"

class Renderer
{
	public:
		Renderer() {};
		virtual ~Renderer() {};

		// Render functions
		virtual void renderEntity(shared_ptr<RenderedEntity> entity) = 0;
		virtual void renderMesh(shared_ptr<Mesh> mesh) = 0;
		virtual void renderTerrain(shared_ptr<Terrain> terrain) = 0;

		virtual void addLight(const Light& light) = 0;
		//	virtual void deleteLight(const UID lightUID) = 0;

		virtual void startFrame() = 0;
		virtual void endFrame() = 0;

		// State changes
		virtual void useMaterial(shared_ptr<Material> material) = 0;

		// Debug functions
		virtual void enableDebugGrid(const bool enable) = 0;
		virtual void enableDebugAxes(const bool enable) = 0;
		virtual void enableLighting(const bool enable) = 0;
		virtual void enableWireframe(const bool enable) = 0;
		virtual void enableTextures(const bool enable) = 0;

		virtual void setWindowSize(const unsigned int width, const unsigned int height) = 0;
		virtual void setCamera(shared_ptr<Camera> camera) = 0;
};

#endif /* RENDERER_HPP_ */
