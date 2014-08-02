#ifndef OGLRENDERER_HPP_
#define OGLRENDERER_HPP_

#include "camera.hpp"
#include "core/definitions.hpp"
#include "core/resourcemanager.hpp"
#include "renderer.hpp"

#define GLM_FORCE_RADIANS
#include <glm/gtc/matrix_transform.hpp>

class OGLRenderer : public Renderer
{
public:
    // We need a resource manager instance to load our shader(-s)
    OGLRenderer(shared_ptr<ResourceManager> resourceManager,
                shared_ptr<Camera>          camera);
    virtual ~OGLRenderer();

    // Render functions
    virtual void renderEntity(shared_ptr<RenderedEntity> entity);
    virtual void renderMesh(shared_ptr<Mesh> mesh);
    virtual void renderTerrain(shared_ptr<Terrain> terrain);

    virtual void addLight(const Light& light);

    virtual void startFrame();
    virtual void endFrame();

    // State changes
    virtual void useMaterial(shared_ptr<Material> material);

    // Debug functions
    virtual void enableDebugGrid(const bool enable);
    virtual void enableDebugAxes(const bool enable);
    virtual void enableLighting(const bool enable);
    virtual void enableWireframe(const bool enable);
    virtual void enableTextures(const bool enable);

    virtual void setWindowSize(const unsigned int width,
                               const unsigned int height);
    virtual void setCamera(shared_ptr<Camera> camera);
protected:
    void drawDebugGrid();
    void initDebugGrid();
    void drawDebugAxes();
    void initDebugAxes();

    inline void updateProjectionMatrix()
    {
        projectionMatrix = glm::perspective(fov, aspectRatio, 0.1f, 1000.0f);
        // send it to the shaders
        colorShader->bind();
        colorShader->setProjectionMatrix(projectionMatrix);
        textureShader->bind();
        textureShader->setProjectionMatrix(projectionMatrix);
        // debugShader->bind();
        // debugShader->setProjectionMatrix(projectionMatrix);
    }

    shared_ptr<ShaderProgram> colorShader;
    shared_ptr<ShaderProgram> textureShader;
    shared_ptr<ShaderProgram> debugShader;
    shared_ptr<Camera>        camera;

    glm::mat4 projectionMatrix;

    float aspectRatio;
    float fov;

    bool         debugGridEnabled;
    unsigned int numDebugGridVertices;
    GLuint       debugGridId;

    bool   debugAxesEnabled;
    GLuint debugAxesId;

    shared_ptr<Material> debugGridMaterial;
    shared_ptr<Material> redMaterial;               // X axis
    shared_ptr<Material> blueMaterial;              // Z axis
    shared_ptr<Material> greenMaterial;             // Y axis
};

#endif /* OGLRENDERER_HPP_ */
