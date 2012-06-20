/*
 * InputManager.cpp
 *
 *  Created on: Jun 10, 2012
 *      Author: zeheron
 */

#include "inputmanager.hpp"

InputManager::InputManager()
{

}

InputManager::~InputManager()
{

}

void InputManager::addListener(InputListener* listener)
{
	vListeners.push_back(listener);
}

void InputManager::removeListener(InputListener* listener)
{
	vListeners.remove(listener);
}

void InputManager::handleUserInput(InputEvent*inEvent)
{
	std::list<InputListener*>::iterator it;
	for (it = vListeners.begin(); it != vListeners.end(); it++)
	{
		(*it)->handleinput(inEvent);
	}
}

