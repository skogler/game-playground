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

void InputManager::addListener(shared_ptr<InputListener> listener)
{
	vListeners.push_back(listener);
}

void InputManager::removeListener(shared_ptr<InputListener> listener)
{
	vListeners.remove(listener);
}

void InputManager::handleUserInput(InputEvent* inEvent)
{
	std::list<shared_ptr<InputListener> >::iterator it;
	for (it = vListeners.begin(); it != vListeners.end(); it++)
	{
		(*it)->handleinput(inEvent);
	}
	delete inEvent; //FIXME: this was a quick fix to prevent memory leak. TODO: Design the system better so this is not necessary
}

