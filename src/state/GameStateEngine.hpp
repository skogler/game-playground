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

class GameState;
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
	sf::RenderWindow window;
	sf::RenderWindow * rw;

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

	sf::RenderWindow* getRw() const {
		return rw;
	}


	//Getters and Setters
	inline void setRunning(bool running)
	{
		this->running = running;
	}

	inline const std::vector<GameState*> & getStates() const
	{
		return states;
	}

	inline bool isRunning() const
	{
		return running;
	}

	inline void quit()
	{
		running = false;
	}
};

#endif /* GAMESTATEENGINE_HPP_ */
