/*
 * gamestateactive.cpp
 *
 *  Created on: Jun 15, 2012
 *      Author: zeheron
 */

#include "gamestateactive.hpp"
#include "../../core/inputmanager.hpp"
#include "../../core/resources/shader.hpp"
#include "../../core/resources/mesh.hpp"
#include "../../graphics/oglrenderer.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <boost/mem_fn.hpp>

using std::string;
using std::list;

#include <iostream>

GameStateActive::GameStateActive(GameStateEngine* game) :
				inputManager(game->getInputManager()),
				freeCam(new FreeMovementCam(game->getWindow())),
				resourceManager(game->getResourceManager()),
				renderer(new OGLRenderer(resourceManager, freeCam))
{
	glm::vec3 cameraPos(0.0f, 0.0f, 20.0f);
	freeCam->setPosition(cameraPos);
//	freeCam->turn(3.14f, 0.0f);
	inputManager->addListener(freeCam);
}

GameStateActive::~GameStateActive()
{
	// TODO Auto-generated destructor stub
}

void GameStateActive::init()
{
	std::string meshName = "pirate";
	shared_ptr<Mesh> mesh = resourceManager->getMesh(meshName);
	mesh->upload();

	m1 = shared_ptr<RenderedEntity>(new RenderedEntity());
	m1->setMesh(mesh);
	glm::vec3 position(5.0f, 0.0f, 0.0f);
	m1->setPosition(position);
	entities.push_back(m1);

	m1 = shared_ptr<RenderedEntity>(new RenderedEntity());
	m1->setMesh(mesh);
	position = glm::vec3(0.0f, 5.0f, 0.0f);
	m1->setPosition(position);
	entities.push_back(m1);

	m1 = shared_ptr<RenderedEntity>(new RenderedEntity());
	m1->setMesh(mesh);
	position = glm::vec3(0.0f, 0.0f, -5.0f);
	m1->setPosition(position);
	entities.push_back(m1);

	m2 = shared_ptr<RenderedEntity>(new RenderedEntity());
	m2->setMesh(mesh);

	entities.push_back(m2);

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
	//m2->turn(-2 * 3.1415926535897f / 300.0f, 0.0f);
	//m1->turn(-2 * 3.1415926535897f / 300.0f, 0.0f);
	//m1->move(20.0f * 3.1415926535897f / 300.0f);
	std::for_each(entities.begin(), entities.end(), boost::mem_fn(&GameEntity::update));
}

void GameStateActive::render()
{
	freeCam->update();
	renderer->startFrame();

	for (list<shared_ptr<RenderedEntity> >::const_iterator i = entities.begin(); i != entities.end(); ++i)
	{
		renderer->renderEntity(*i);
	}
	//draw ground is only for testing
	renderer->endFrame();
}


