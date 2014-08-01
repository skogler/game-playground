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

void InputManager::handleUserInput(InputEvent& inEvent)
{
    for (const auto& listener : vListeners)
    {
        listener->handleinput(inEvent);
    }
}
