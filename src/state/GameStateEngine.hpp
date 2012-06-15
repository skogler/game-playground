/*
 * GameStateEngine.hpp
 *
 *  Created on: Jun 11, 2012
 *      Author: zeheron
 */

#ifndef GAMESTATEENGINE_HPP_
#define GAMESTATEENGINE_HPP_

#include <vector>
#include <sstream>
#include <iostream>
#include <boost/thread.hpp>

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../utils/config.h"
#include "../utils/FPSManager.hpp"
#include "../core/inputmanager.hpp"
#include "../core/inputmapper.hpp"


class GameState;
class GameStateEngine {
private:
	bool running;
	// the stack of states
	std::vector<GameState*> states;

	//Input
	InputManager* inputManager;
	InputMapper* inputMapper;

	//OpenGL context-settings and window
	sf::ContextSettings contextSettings;
	sf::RenderWindow window;

public:
	GameStateEngine();
	virtual ~GameStateEngine();

	bool init();
	void cleanup();

	void changeGameState(GameState* state);
	void pushState(GameState* state);
	void popState();

	void handleInput();
	void update();
	void render();

	//Getters and Setters

	InputManager* getInputManager() const {
		return inputManager;
	}

	void setRunning(bool running) {
		this->running = running;
	}

	std::vector<GameState*> getStates() const {
		return states;
	}

	bool isRunning() {
		return running;
	}
	void Quit() {
		running = false;
	}

};

#endif /* GAMESTATEENGINE_HPP_ */
