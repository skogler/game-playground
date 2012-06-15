/*
 * InputManager.cpp
 *
 *  Created on: Jun 10, 2012
 *      Author: zeheron
 */

#include "inputmanager.hpp"

InputManager* InputManager::imInstance = NULL;

InputManager::InputManager() {
	// TODO gonna be deleted
}

InputManager::~InputManager() {
	// TODO Auto-generated destructor stub
}


InputManager* InputManager::instance()
{
  if (imInstance == NULL)
	  imInstance = new InputManager();

  return imInstance;
}

void InputManager::addListener(InputListener* listener) {
	vListeners.push_back(listener);
}

void InputManager::removeListener(InputListener* listener) {
	vListeners.remove(listener);
}

void InputManager::handleUserInput(InputEvent*inEvent) {
	std::list<InputListener*>::iterator it;
	for( it = vListeners.begin(); it != vListeners.end() ;it++)
	{
		 (*it)->handleinput(inEvent);
	}

}


