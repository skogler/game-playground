/*
 * InputMapper.cpp
 *
 *  Created on: Jun 13, 2012
 *      Author: zeheron
 */

#include "inputmapper.hpp"
#include <iostream>

InputMapper::InputMapper() 
    : keyboardActionMap()
    , keyboardStateMap()
    , actionSet()
    , stateSet()
    , mouseMoved(false)
    , currentInputEvent{actionSet, stateSet, mouseMoved}
{
	// TODO: Refactor this  so the assignments are read from a config file.
	keyboardActionMap[sf::Keyboard::A] = ACTION_CAMERA_MOVE_LEFT;
	keyboardActionMap[sf::Keyboard::D] = ACTION_CAMERA_MOVE_RIGHT;

	keyboardActionMap[sf::Keyboard::Right] = ACTION_CAMERA_TURN_RIGHT;
	keyboardActionMap[sf::Keyboard::Left] = ACTION_CAMERA_TURN_LEFT;
	keyboardActionMap[sf::Keyboard::Up] = ACTION_CAMERA_TURN_UP;
	keyboardActionMap[sf::Keyboard::Down] = ACTION_CAMERA_TURN_DOWN;

	//Important
	keyboardStateMap[sf::Keyboard::W] = STATE_CAMERA_MOVING_FORWARD;
	keyboardStateMap[sf::Keyboard::S] = STATE_CAMERA_MOVING_BACK;
	keyboardStateMap[sf::Keyboard::A] = STATE_CAMERA_MOVE_LEFT;
	keyboardStateMap[sf::Keyboard::D] = STATE_CAMERA_MOVE_RIGHT;
}

InputMapper::~InputMapper()
{
}

InputEvent& InputMapper::retrieveInputEvent()
{
	return currentInputEvent;
}

/**
 * This function takes the SFML Event and  creates the current InputEvent
 * out of the extracted data.
 */
void InputMapper::mapInputEvent(sf::Event event)
{
	//TODO handle mouse input
	if (event.type == sf::Event::KeyPressed)
	{
		//States
		itKStateMap = keyboardStateMap.find(event.key.code);
		if (itKStateMap != keyboardStateMap.end())
			stateSet.insert(itKStateMap->second);
		else
		{
			//Actions
			itKActionMap = keyboardActionMap.find(event.key.code);
			if (itKActionMap != keyboardActionMap.end())
				actionSet.insert(itKActionMap->second);
		}

	}
	else if (event.type == sf::Event::KeyReleased)
	{  // Handle state release
		itKStateMap = keyboardStateMap.find(event.key.code);
		if (itKStateMap != keyboardStateMap.end())
		{
			itStateSet = stateSet.find(itKStateMap->second);
			if (itKStateMap != keyboardStateMap.end())
				stateSet.erase(itStateSet);
		}
	}
	if (event.type == sf::Event::MouseMoved)
		actionSet.insert(ACTION_MOUSE_MOVED);
}

void InputMapper::endFrame()
{
    actionSet.clear();
}
