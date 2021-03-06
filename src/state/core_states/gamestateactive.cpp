/*
 * gamestateactive.cpp
 *
 *  Created on: Jun 15, 2012
 *      Author: zeheron
 */

#include "core/inputmanager.hpp"
#include "core/resources/mesh.hpp"
#include "gamestateactive.hpp"
#include "graphics/graphics-definitions.hpp"
#include "graphics/oglrenderer.hpp"
#include "graphics/shaderprogram.hpp"

#include <boost/mem_fn.hpp>
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using std::string;
using std::list;

#include <iostream>

GameStateActive::GameStateActive(shared_ptr<Renderer>        renderer,
                                 shared_ptr<InputManager>    inputManager,
                                 shared_ptr<ResourceManager> resourceManager) :
    inputManager(inputManager),
    resourceManager(resourceManager),
    freeCam(new FreeMovementCam()),
    renderer(renderer)
{
    glm::vec3 cameraPos(0.0f, 0.0f, 20.0f);

    freeCam->setPosition(cameraPos);
    inputManager->addListener(freeCam);
    renderer->setCamera(freeCam);
}

GameStateActive::~GameStateActive()
{
    // TODO Auto-generated destructor stub
}

void GameStateActive::init()
{
    // MANY PIRATES DEMO CODE:
    std::string meshName = "test";

    shared_ptr<Mesh> mesh = resourceManager->getMesh(meshName);
    mesh->upload();

    for (int x_coord = -50; x_coord < 50; x_coord += 5)
    {
        for (int z_coord = -50; z_coord < 50; z_coord += 5)
        {
            shared_ptr<RenderedEntity> re = shared_ptr<RenderedEntity>(
                new RenderedEntity());
            re->setMesh(mesh);
            glm::vec3 position(x_coord, 0.0f, z_coord);
            re->setPosition(position);
            re->rotateX(-1.57f);
            re->update();
            entities.push_back(re);
        }
    }
    // m1 = shared_ptr<RenderedEntity>(new RenderedEntity());
    // m1->setMesh(mesh);
    // glm::vec3 position(0.0f, 5.0f, 0.0f);
    // m1->setPosition(position);
    // m1->rotateX(-1.57f);
    // entities.push_back(m1);

    glm::vec3 whiteLightPosition(0.0f, 1000.0f, 1000.0f);
    Light     whiteLight(whiteLightPosition);
    whiteLight.setIntensity(1.0f);
    whiteLight.setLinearAttenuation(0.0f);
    whiteLight.setSquaredAttenuation(0.0f);
    renderer->addLight(whiteLight);

    renderer->enableDebugGrid(false);
    renderer->enableDebugAxes(false);
}

void GameStateActive::cleanup()
{
}

void GameStateActive::pause()
{
}

void GameStateActive::resume()
{
}

void GameStateActive::handleEvents(InputEvent& inputEvent)
{
    inputManager->handleUserInput(inputEvent);
}

void GameStateActive::update()
{
    freeCam->update();
    // m1->turn(-2 * 3.1415926535897f / 300.0f, 0.0f);
    // m1->move(20.0f * 3.1415926535897f / 300.0f);
    // m1->rotateY(0.01f);
    std::for_each(entities.begin(), entities.end(),
                  boost::mem_fn(&GameEntity::update));
}

void GameStateActive::render()
{

    renderer->startFrame();

    for (const auto& entity : entities)
    {
        renderer->renderEntity(entity);
    }
    renderer->endFrame();
}
