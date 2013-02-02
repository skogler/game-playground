/*
 * gamestateactive.cpp
 *
 *  Created on: Jun 15, 2012
 *      Author: zeheron
 */

#include "gamestateactive.hpp"
#include "core/inputmanager.hpp"
#include "graphics/shaderprogram.hpp"
#include "core/resources/mesh.hpp"
#include "graphics/oglrenderer.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <boost/mem_fn.hpp>

using std::string;
using std::list;

#include <iostream>

GameStateActive::GameStateActive(shared_ptr<Renderer> renderer,
		shared_ptr<InputManager> inputManager,
		shared_ptr<ResourceManager> resourceManager,
		shared_ptr<sf::Window> window) :
				inputManager(inputManager),
				resourceManager(resourceManager),
				freeCam(new FreeMovementCam(window)),
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
	std::string meshName = "test";
	shared_ptr<Mesh> mesh = resourceManager->getMesh(meshName);
	mesh->upload();

//	//Terrain init
//	terrain = shared_ptr<Terrain>(new Terrain());
//	terrain->init();
  for (int x_coord = -50; x_coord < 50; x_coord += 5)
  {
    for (int z_coord = -50; z_coord < 50; z_coord += 5)
    {
      shared_ptr<RenderedEntity> re = shared_ptr<RenderedEntity>(new RenderedEntity());
      re->setMesh(mesh);
      glm::vec3 position(x_coord, 0.0f, z_coord);
      re->setPosition(position);
      re->rotateX(-1.57f);
      //re->rotateZ(-1.57f);
      entities.push_back(re);
    }
  }
	m1 = shared_ptr<RenderedEntity>(new RenderedEntity());
	m1->setMesh(mesh);
	glm::vec3 position(0.0f, 5.0f, 0.0f);
	m1->setPosition(position);
	m1->rotateX(-1.57f);
	m1->rotateZ(-1.57f);
	entities.push_back(m1);

//	m2 = shared_ptr<RenderedEntity>(new RenderedEntity());
//	m2->setMesh(mesh);
//	position = glm::vec3(0.0f, 0.0f, 0.0f);
//	m2->setPosition(position);
//	m2->rotateX(-1.57f);
//	entities.push_back(m2);

	glm::vec3 whiteLightPosition(0.0f, 1000.0f, 1000.0f);
	Light whiteLight(whiteLightPosition);
	whiteLight.setIntensity(1.0f);
	whiteLight.setLinearAttenuation(0.0f);
	whiteLight.setSquaredAttenuation(0.0f);
	renderer->addLight(whiteLight);

	renderer->enableDebugGrid(true);
	renderer->enableDebugAxes(true);
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

void GameStateActive::handleEvents(InputEvent* inputEvent)
{
	inputManager->handleUserInput(inputEvent);
}

void GameStateActive::update()
{
	freeCam->update();
	//m1->turn(-2 * 3.1415926535897f / 300.0f, 0.0f);
	//m1->move(20.0f * 3.1415926535897f / 300.0f);
	m1->rotateZ(0.01f);
//	m1->rotateX(0.01f);
	std::for_each(entities.begin(), entities.end(),
			boost::mem_fn(&GameEntity::update));
}

void GameStateActive::render()
{
	renderer->startFrame();

	for (list<shared_ptr<RenderedEntity> >::const_iterator i = entities.begin(); i != entities.end(); ++i)
	{
		renderer->renderEntity(*i);
	}
	renderer->endFrame();
	//terrain->render();
	//terrain->renderTest();
}
