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

#include "utils/config.h"
#include "utils/FPSManager.hpp"
#include "core/inputmanager.hpp"
#include "core/inputmapper.hpp"
#include "core/resourcemanager.hpp"
#include "graphics/renderer.hpp"
#include "graphics/camera.hpp"
#include "gamestate.hpp"

class GameStateEngine
{
private:
	bool running;
	// the stack of states
	std::vector<shared_ptr<GameState>> states;

	//Input
	shared_ptr<InputManager> inputManager;
	boost::scoped_ptr<InputMapper> inputMapper;

	// Resource Manager
	shared_ptr<ResourceManager> resourceManager;

	//OpenGL context-settings and window
	sf::ContextSettings contextSettings;
	shared_ptr<sf::Window> window;

	shared_ptr<FPSManager> fpsManager;
	shared_ptr<Renderer> renderer;
	shared_ptr<Camera> defaultCamera;

public:
	GameStateEngine(shared_ptr<FPSManager> fpsManager);
	virtual ~GameStateEngine();

	bool init();

	void changeGameState(shared_ptr<GameState> state);
	void pushState(shared_ptr<GameState> state);
	void popState();

	void handleInput();
	void update();
	void render();
	void updateWindow();

	inline shared_ptr<Renderer> getRenderer() const
	{
		return renderer;
	}

	inline shared_ptr<ResourceManager> getResourceManager()
	{
		return resourceManager;
	}

	inline shared_ptr<InputManager> getInputManager()
	{
		return inputManager;
	}

	inline shared_ptr<sf::Window> getWindow()
	{
		return window;
	}

	//Getters and Setters
	inline const std::vector<shared_ptr<GameState>> & getStates() const
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
