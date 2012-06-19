/*
 * gamestateactive.cpp
 *
 *  Created on: Jun 15, 2012
 *      Author: zeheron
 */

#include "gamestateactive.hpp"
#include "../../core/inputmanager.hpp"
#include "../../graphics/resources/shader.hpp"
using std::string;
using std::list;
using boost::shared_ptr;

#include <iostream>

GameStateActive::GameStateActive()
{
	inputManager = InputManager::instance();
	camera = new Camera();
	camera->move(-20.0f);
	inputManager->addListener(camera);
	init();
}

GameStateActive::~GameStateActive()
{
	// TODO Auto-generated destructor stub
}

void GameStateActive::init()
{
	modelMatrix = 0;
	viewMatrix = 0;
	projectionMatrix = 0;
	std::string filename = "resources/models/monkey.m42";
	shared_ptr<Mesh> mesh(new Mesh(filename));
	mesh->upload();

	m1 = boost::shared_ptr<RenderedEntity>(new RenderedEntity());
	m1->set_mesh(mesh);
	glm::vec3 position(10.0f, 0.0f, 0.0f);
	m1->set_position(position);

	entities.push_back(m1);

	m2 = boost::shared_ptr<RenderedEntity>(new RenderedEntity());
	m2->set_mesh(mesh);

	entities.push_back(m2);

	Shader shader("default", "default");
	shader.bind();
	GLuint program = shader.get_id();

	modelMatrix = glGetUniformLocation(program, "modelMatrix");
	viewMatrix = glGetUniformLocation(program, "viewMatrix");
	projectionMatrix = glGetUniformLocation(program, "projectionMatrix");

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
}

void GameStateActive::cleanup()
{
}

void GameStateActive::pause()
{
}

void GameStateActive::Resume()
{
}

void GameStateActive::handleEvents(InputEvent* inputEvent)
{
	inputManager->handleUserInput(inputEvent);
}

void GameStateActive::update(GameStateEngine* game)
{
	m2->turn(-2 * 3.1415926535897f / 300.0f, 0.0f);
	m1->turn(-2 * 3.1415926535897f / 300.0f, 0.0f);
	m1->move(20.0f * 3.1415926535897f / 300.0f);
}

void GameStateActive::render(GameStateEngine* game)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// set the view matrix = model matrix of the camera
	glUniformMatrix4fv(viewMatrix, 1, GL_FALSE, &camera->get_modelMatrix()[0][0]);
	// set the projection matrix
	glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE, &camera->get_projectionMatrix()[0][0]);

	for (list<shared_ptr<RenderedEntity> >::const_iterator i = entities.begin(); i != entities.end(); ++i)
	{
		// set the model matrix for each rendered entity
		glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, &(*i)->get_modelMatrix()[0][0]);
		(*i)->render();
	}

}

