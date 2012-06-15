/*
 * gamestateactive.cpp
 *
 *  Created on: Jun 15, 2012
 *      Author: zeheron
 */

#include "gamestateactive.hpp"
#include "../../core/inputmanager.hpp"

GameStateActive::GameStateActive() {
	inputManager = 	InputManager::instance();
}

GameStateActive::~GameStateActive() {
	// TODO Auto-generated destructor stub
}

void GameStateActive::init() {
}

void GameStateActive::cleanup() {
}

void GameStateActive::pause() {
}

void GameStateActive::Resume() {
}

void GameStateActive::handleEvents(InputEvent* inputEvent) {
	inputManager->handleUserInput(inputEvent);
}

void GameStateActive::update(GameStateEngine* game) {
}

void GameStateActive::render(GameStateEngine* game) {
}


