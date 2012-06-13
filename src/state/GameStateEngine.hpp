/*
 * GameStateEngine.hpp
 *
 *  Created on: Jun 11, 2012
 *      Author: zeheron
 */

#ifndef GAMESTATEENGINE_HPP_
#define GAMESTATEENGINE_HPP_

#include <vector>

class GameState;
class GameStateEngine {
public:
	GameStateEngine();
	virtual ~GameStateEngine();

	void init();
	void cleanup();

	void changeGameState(GameState* state);
	void pushState(GameState* state);
	void popState();

	void handleEvents();
	void update();
	void render();

	bool isRunning() {
		return running;
	}
	void Quit() {
		running = false;
	}

private:
	// the stack of states
	std::vector<GameState*> states;

	bool running;
};

#endif /* GAMESTATEENGINE_HPP_ */
