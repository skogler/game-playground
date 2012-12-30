/*
 * GameStateEngine.cpp
 *
 *  Created on: Jun 11, 2012
 *      Author: zeheron
 */

#include "GameStateEngine.hpp"

#include "gamestate.hpp"
#include "core/resourcemanager.hpp"
#include "graphics/oglrenderer.hpp"
#include "graphics/cameras/freemovementcam.hpp"
#include "graphics/cameras/noopcamera.hpp"
#include "utils/logger.hpp"

#include <iostream>
#include <boost/filesystem.hpp>

GameStateEngine::GameStateEngine(shared_ptr<FPSManager> fpsManager) :
				inputManager(new InputManager),
				inputMapper(new InputMapper),
				resourceManager(new ResourceManager(boost::filesystem::path("resources"))),
				window(new sf::RenderWindow()),
				fpsManager(fpsManager),
				defaultCamera(new NoOpCamera())
{
}

GameStateEngine::~GameStateEngine()
{
  window->close();
}

/**
 * Initializes the GameStateEngine
 */
bool GameStateEngine::init()
{
	running = true;

	//OpenGL Context settings: depthBits, stencilBits, AA, major & minor version
	contextSettings.depthBits = 24;
	contextSettings.stencilBits = 8;
	contextSettings.antialiasingLevel = 4;
	contextSettings.majorVersion = 4;
	contextSettings.minorVersion = 2;

  window->create(sf::VideoMode(1024, 768, 32), "game-playground", sf::Style::Default, contextSettings);
//	window->create(sf::VideoMode::getFullscreenModes()[0], "game-playground", sf::Style::Close | sf::Style::Fullscreen, contextSettings);

	window->setFramerateLimit(50);

	//Glew error checking
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		throw std::runtime_error("Error initializing OpenGL(GLEW), maybe because of no/old video driver.");
	}

	window->display();

	renderer = shared_ptr<Renderer>(new OGLRenderer(resourceManager, defaultCamera));
	renderer->setWindowSize(window->getSize().x, window->getSize().y);

	return true;
}

void GameStateEngine::changeGameState(shared_ptr<GameState> state)
{
	this->pushState(state);
}

/*
 * Adds a new state to the vector stack
 */
void GameStateEngine::pushState(shared_ptr<GameState> state)
{
	state->init();
	states.push_back(state);
}

/*
 * Removes the last state
 */
void GameStateEngine::popState()
{
    shared_ptr<GameState> last = states.back();
    states.pop_back();
}

/*
 * This function will execute the input event handling of the last state in the vector.
 */
void GameStateEngine::handleInput()
{
	sf::Event event;
	shared_ptr<GameState> gstate = states.back();
	while (window->pollEvent(event))
	{
		//TODO: remove check for exit
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			quit();
		inputMapper->mapInputEvent(event);
	}
	gstate->handleEvents(inputMapper->retrieveInputEvent());
}

/*
 * This function will execute the world update of the last state in the vector.
 */
void GameStateEngine::update()
{
	shared_ptr<GameState> gstate = states.back();
	gstate->update();
}

/*
 * This function will execute the rendering of the last state in the vector.
 */
void GameStateEngine::render()
{
	shared_ptr<GameState> gstate = states.back();
	gstate->render();
}

void GameStateEngine::updateWindow()
{
	window->display();
}

