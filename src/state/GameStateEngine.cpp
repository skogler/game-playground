/*
 * GameStateEngine.cpp
 *
 *  Created on: Jun 11, 2012
 *      Author: zeheron
 */

#include "GameStateEngine.hpp"

#include "gamestate.hpp"
#include "../core/resourcemanager.hpp"

#include <iostream>
#include <boost/filesystem.hpp>

GameStateEngine::GameStateEngine() :
		inputManager(new InputManager),
		inputMapper(new InputMapper),
		resourceManager(new ResourceManager(boost::filesystem::path("resources")))
{

}

GameStateEngine::~GameStateEngine() {
	// TODO Auto-generated destructor stub
}

/**
 * Initializes the GameStateEngine
 */
bool GameStateEngine::init() {
	running = true;

	//OpenGL Context settings: depthBits, stencilBits, AA, major & minor version
	contextSettings.depthBits = 24;
	contextSettings.stencilBits = 8;
	contextSettings.antialiasingLevel = 4;
	contextSettings.majorVersion = 4;
	contextSettings.minorVersion = 2;
	window.create(sf::VideoMode(1024, 768, 32), "game-playground",
			sf::Style::Close, contextSettings);

	window.setFramerateLimit(70);

	//Glew error checking
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		return false;
	}

	window.display();
	rw = &window;

	return true;
}

void GameStateEngine::cleanup() {
	// TODO Clean up after awesomeness
}

void GameStateEngine::changeGameState(GameState* state) {
	//TODO: update stack in a appropriate manner
	this->pushState(state);
}

/*
 * Adds a new state to the vector stack
 */
void GameStateEngine::pushState(GameState* state) {
	states.push_back(state);
}

/*
 * Removes the last state
 */
void GameStateEngine::popState() {
	states.pop_back();
}

/*
 * This function will execute the input event handling of the last state in the vector.
 */
void GameStateEngine::handleInput() {
	sf::Event event;
	GameState* gstate = states.back();
	while (window.pollEvent(event)) {
		//TODO: remove check for exit
		if (event.key.code == sf::Keyboard::Escape)
			running = false;
		inputMapper->mapInputEvent(event);

	}
	gstate->handleEvents(inputMapper->retrieveInputEvent());
}

/*
 * This function will execute the world update of the last state in the vector.
 */
void GameStateEngine::update() {
	GameState* gstate = states.back();
	gstate->update(this);
}

/*
 * This function will execute the rendering of the last state in the vector.
 */
void GameStateEngine::render() {
	GameState* gstate = states.back();
	gstate->render(this);
}

void GameStateEngine::updateWindow() {
	window.display();
}

