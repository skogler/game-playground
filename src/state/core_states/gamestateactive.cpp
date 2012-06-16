/*
 * gamestateactive.cpp
 *
 *  Created on: Jun 15, 2012
 *      Author: zeheron
 */

#include "gamestateactive.hpp"
#include "../../core/inputmanager.hpp"
#include "../../graphics/shader.hpp"
using std::string;
using std::list;
using boost::shared_ptr;

#include <iostream>


GameStateActive::GameStateActive() {
	inputManager = InputManager::instance();
	camera = new Camera();
	camera->move(-20.0f);
	init();
}

GameStateActive::~GameStateActive() {
	// TODO Auto-generated destructor stub
}

void GameStateActive::init() {
	modelMatrix = 0;
	viewMatrix = 0;
	projectionMatrix = 0;
	std::string filename = "resources/models/monkey.m42";
	Mesh * mesh = new Mesh(filename);
	mesh->upload();

	shared_ptr<RenderedEntity> monkey(new RenderedEntity());
	monkey->set_mesh(mesh);
	entities.push_back(monkey);

	Shader shader("default", "default");
	shader.bind();
	GLuint program = shader.get_id();

	modelMatrix = glGetUniformLocation(program, "modelMatrix");
	viewMatrix = glGetUniformLocation(program, "viewMatrix");
	projectionMatrix = glGetUniformLocation(program, "projectionMatrix");

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void GameStateActive::cleanup() {
}

void GameStateActive::pause() {
}

void GameStateActive::Resume() {
}

void GameStateActive::handleEvents(InputEvent* inputEvent) {
	inputManager->handleUserInput(inputEvent);
}

void GameStateActive::update(GameStateEngine* game) {
}

void GameStateActive::render(GameStateEngine* game) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// set the view matrix = model matrix of the camera
	glUniformMatrix4fv(viewMatrix, 1, GL_FALSE,
			&camera->get_modelMatrix()[0][0]);
	// set the projection matrix
	glUniformMatrix4fv(projectionMatrix, 1, GL_FALSE,
			&camera->get_projectionMatrix()[0][0]);

	for (list<shared_ptr<RenderedEntity> >::const_iterator i = entities.begin();
			i != entities.end(); ++i) {
		// set the model matrix for each rendered entity
		glUniformMatrix4fv(modelMatrix, 1, GL_FALSE,
				&(*i)->get_modelMatrix()[0][0]);
		(*i)->render();
	}

}

