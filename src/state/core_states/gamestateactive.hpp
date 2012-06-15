/*
 * gamestateactive.hpp
 *
 *  Created on: Jun 15, 2012
 *      Author: zeheron
 */

#ifndef GAMESTATEACTIVE_HPP_
#define GAMESTATEACTIVE_HPP_

#include "../gamestate.hpp"

class GameStateActive: public GameState {
public:
	GameStateActive();
	virtual ~GameStateActive();

	void init();
	void cleanup();

	void pause();
	void Resume();

	void handleEvents(InputEvent* inputEvent);
	void update(GameStateEngine* game);
	void render(GameStateEngine* game);

private:
	InputManager* inputManager;

};

#endif /* GAMESTATEACTIVE_HPP_ */
