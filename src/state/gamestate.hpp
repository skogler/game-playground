/*
 * GameState.hpp
 *
 *  Created on: Jun 11, 2012
 *      Author: zeheron
 */

#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include "core/inputevent.hpp"

class GameState
{

	public:
		virtual void init() = 0;
		virtual void cleanup() = 0;

		virtual void pause() = 0;
		virtual void resume() = 0;

		virtual void handleEvents(InputEvent* inputEvent) = 0;
		virtual void update() = 0;
		virtual void render() = 0;

		GameState() {};
		virtual ~GameState() {};
	protected:

};

#endif /* GAMESTATE_HPP_ */
