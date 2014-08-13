#include "oglrenderer.hpp"

#include "graphics/graphics-definitions.hpp"
#include "graphics/shaderprogram.hpp"
#include "utils/logger.hpp"

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>

#include <GL/glew.h>
#include <boost/format.hpp>
#include <iostream>
#include <vector>
using std::vector;

/**
 * Load our default shader on creation.
 */
OGLRenderer::OGLRenderer(shared_ptr<ResourceManager> resourceManager,
                         shared_ptr<Camera>          camera) :
    colorShader(new ShaderProgram()),
    textureShader(new ShaderProgram()),
    debugShader(new ShaderProgram()),
    camera(camera),
    aspectRatio(10.0f),
    fov(45.0f),
    debugGridEnabled(false),
    debugAxesEnabled(false),
    debugGridMaterial(resourceManager->getMaterial("debug")),
    redMaterial(resourceManager->getMaterial("debugRed")),
    blueMaterial(resourceManager->getMaterial("debugBlue")),
    greenMaterial(resourceManager->getMaterial("debugGreen"))
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

    // initDebugGrid();
    // initDebugAxes();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);

    glUseProgram(0);

    // CEGUI initialization
    CEGUI::OpenGL3Renderer::bootstrapSystem();

    // initialise the required dirs for the DefaultResourceProvider
    CEGUI::DefaultResourceProvider* rp =
        static_cast<CEGUI::DefaultResourceProvider*>
        (CEGUI::System::getSingleton().
         getResourceProvider());

    rp->setResourceGroupDirectory("schemes", "resources/gui/schemes/");
    CEGUI::Scheme::setDefaultResourceGroup("schemes");

    rp->setResourceGroupDirectory("imagesets", "resources/gui/imagesets/");
    CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");

    rp->setResourceGroupDirectory("fonts", "resources/gui/fonts/");
    CEGUI::Font::setDefaultResourceGroup("fonts");

    rp->setResourceGroupDirectory("layouts", "resources/gui/layouts/");
    CEGUI::WindowManager::setDefaultResourceGroup("layouts");

    rp->setResourceGroupDirectory("looknfeel", "resources/gui/looknfeel/");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeel");

    rp->setResourceGroupDirectory("lua-scripts", "resources/gui/lua_scripts/");
    CEGUI::ScriptModule::setDefaultResourceGroup("lua-scripts");

    rp->setResourceGroupDirectory("schemas", "resources/gui/xml_schemas/");
    // If an XML parser with validation support is used, set the schema
    // directory
    CEGUI::XMLParser* parser = CEGUI::System::getSingleton().getXMLParser();
    if (parser->isPropertyPresent("SchemaDefaultResourceGroup"))
    {
        parser->setProperty("SchemaDefaultResourceGroup", "schemas");
    }

    CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
    // The first font loaded automatically becomes the default font, but note
    // that the scheme might have already loaded a font, so there may already
    // be a default set - if we want the "DejaVuSans-10" font to definitely
    // be the default, we should set the default explicitly afterwards.
    CEGUI::FontManager::getSingleton().createFromFile("DejaVuSans-10.font");

    CEGUI::WindowManager& wmgr   = CEGUI::WindowManager::getSingleton();
    CEGUI::Window*        myRoot = wmgr.loadLayoutFromFile("HUD.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(myRoot);
}

OGLRenderer::~OGLRenderer()
{
    // glDeleteBuffers(1, &debugGridId);
    // glDeleteBuffers(1, &debugAxesId);
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
    glBindVertexArray(mesh->getVertexArrayObject());
    vector<FaceGroup>&          faceGroups = mesh->getFaceGroups();
    vector<FaceGroup>::iterator iter;
    for (iter = faceGroups.begin(); iter < faceGroups.end(); ++iter)
    {
        shared_ptr<Material> mat = mesh->getMaterial(iter->materialName);
        if (mat->getType() == MATERIAL_TYPE_COLOR)
        {
            colorShader->bind();
            colorShader->setMaterial(*mat);
        }
        else if (mat->getType() == MATERIAL_TYPE_TEXTURE)
        {
            textureShader->bind();
            textureShader->setMaterial(*mat);
        }
        glDrawElements(GL_TRIANGLES,
                       iter->size * 3,
                       GL_UNSIGNED_INT,
                       BUFFER_OFFSET(sizeof(GLuint) * 3 * iter->start));
    }
    glBindVertexArray(0);
}

void OGLRenderer::useMaterial(shared_ptr<Material> material)
{
    if (material->getType() == MATERIAL_TYPE_COLOR)
    {
        colorShader->bind();
        colorShader->setMaterial(*material);
    }
    else if (material->getType() == MATERIAL_TYPE_TEXTURE)
    {
        textureShader->bind();
        textureShader->setMaterial(*material);
    }
}

void OGLRenderer::enableDebugGrid(const bool show)
{
    debugGridEnabled = show;
}

void OGLRenderer::setWindowSize(const unsigned int width,
                                const unsigned int height)
{
    glViewport(0, 0, width, height);
    aspectRatio = (float) width / (float) height;
    updateProjectionMatrix();
    CEGUI::System::getSingleton().notifyDisplaySizeChanged(CEGUI::Sizef(width,
                                                                        height));
}

void OGLRenderer::startFrame()
{
    CEGUI::System::getSingleton().injectTimePulse(0.1f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    glDepthFunc(GL_LESS);
    glUseProgram(0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    colorShader->bind();
    colorShader->setViewMatrix(camera->getModelMatrix());
    textureShader->bind();
    textureShader->setViewMatrix(camera->getModelMatrix());
}

void OGLRenderer::endFrame()
{
    // if (debugAxesEnabled || debugGridEnabled) {
    // debugShader->bind();
    //// draw debug stuff always in world coordinates
    // debugShader->setModelMatrix(IDENTITY_MATRIX);
    // debugShader->setViewMatrix(camera->getModelMatrix());
    // debugShader->setProjectionMatrix(projectionMatrix);
    // if (debugAxesEnabled) {
    // drawDebugAxes();
    // }
    // if (debugGridEnabled) {
    // drawDebugGrid();
    // }
    // }
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
    glUseProgram(0);

    CEGUI::System::getSingleton().renderAllGUIContexts();
}

void OGLRenderer::drawDebugGrid()
{
    debugShader->setMaterial(*debugGridMaterial);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, debugGridId);
    glVertexAttribPointer(0,        // attribute
                          3,        // size
                          GL_FLOAT, // type
                          GL_FALSE, // normalized?
                          0,        // stride
                          (void*) 0 // array
                                    // buffer
                                    // offset
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
    GLfloat extent = 1000.0f;     // How far on the Z-Axis and X-Axis
                                  // the ground extends
    GLfloat stepSize = 50.0f;     // The size of the separation between
                                  // points
    GLfloat groundLevel = -0.05f; // Where on the Y-Axis the ground is
                                  // drawn

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
    glBufferData(GL_ARRAY_BUFFER,
                 debugGridVertices.size() * sizeof(glm::vec3),
                 &debugGridVertices[0],
                 GL_STATIC_DRAW);
    numDebugGridVertices = debugGridVertices.size();
}

void OGLRenderer::drawDebugAxes()
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, debugAxesId);
    glVertexAttribPointer(0,        // attribute
                          3,        // size
                          GL_FLOAT, // type
                          GL_FALSE, // normalized?
                          0,        // stride
                          (void*) 0 // array
                                    // buffer
                                    // offset
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
    glBufferData(GL_ARRAY_BUFFER,
                 6 * sizeof(glm::vec3),
                 &debugAxesVertices[0],
                 GL_STATIC_DRAW);
}
