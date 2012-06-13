/*
 * GameState.hpp
 *
 *  Created on: Jun 11, 2012
 *      Author: zeheron
 */

#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include "GameStateEngine.hpp"

class GameState {

public:
	virtual void init() = 0;
	virtual void cleanup() = 0;

	virtual void pause() = 0;
	virtual void Resume() = 0;

	virtual void handleEvents(GameStateEngine* game) = 0;
	virtual void update(GameStateEngine* game) = 0;
	virtual void render(GameStateEngine* game) = 0;

	void changeState(GameStateEngine* game, GameState* state) {
		game->changeGameState(state);
	}

protected:
	GameState() {};
	virtual ~GameState(){};

};

#endif /* GAMESTATE_HPP_ */
