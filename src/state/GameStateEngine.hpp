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
#include "../core/resourcemanager.hpp"
#include "gamestate.hpp"

class GameStateEngine
{
private:
	bool running;
	// the stack of states
	std::vector<GameState*> states;

	//Input
	boost::shared_ptr<InputManager> inputManager;
	boost::scoped_ptr<InputMapper> inputMapper;

	// Resource Manager
	boost::shared_ptr<ResourceManager> resourceManager;

	//OpenGL context-settings and window
	sf::ContextSettings contextSettings;
	boost::shared_ptr<sf::RenderWindow> window;

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
	void updateWindow();

	inline boost::shared_ptr<ResourceManager> getResourceManager()
	{
		return resourceManager;
	}

	inline boost::shared_ptr<InputManager> getInputManager()
	{
		return inputManager;
	}

	inline boost::shared_ptr<sf::RenderWindow> getWindow()
	{
		return window;
	}

	//Getters and Setters
	inline const std::vector<GameState*> & getStates() const
	{
		return states;
	}

	inline bool isRunning() const
	{
		return running;
	}

	inline void start()
	{
		running = true;
	}

	inline void quit()
	{
		running = false;
	}
};

#endif /* GAMESTATEENGINE_HPP_ */
