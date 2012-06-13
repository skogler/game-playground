/*
 * GameStateEngine.cpp
 *
 *  Created on: Jun 11, 2012
 *      Author: zeheron
 */

#include "GameStateEngine.hpp"
#include "GameState.hpp"

GameStateEngine::GameStateEngine() {
	// TODO Auto-generated constructor stub

}

GameStateEngine::~GameStateEngine() {
	// TODO Auto-generated destructor stub
}

void GameStateEngine::init() {
	// TODO Initalize
}

void GameStateEngine::cleanup() {
	// TODO Clean up after awesomeness
}

void GameStateEngine::changeGameState(GameState* state) {

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
 * This function will execute the event handling of the last state in the vector.
 */
void GameStateEngine::handleEvents() {
	GameState* gstate = states.back();
	gstate->update(this);

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
	gstate->update(this);
}

