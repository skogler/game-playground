/*
 * InputMapper.cpp
 *
 *  Created on: Jun 13, 2012
 *      Author: zeheron
 */

#include "inputmapper.hpp"

InputMapper::InputMapper() {

	// TODO: Refactor this shit so the assignments are read from a config file.
	// for testing purpose its is EXTREMELY imports that state and action have no redundant keybindings
	// otherwise IMPENDING DOOM
	keyboardActionMap[sf::Keyboard::Left] = ACTION_CAMERA_TURN_LEFT;
	keyboardActionMap[sf::Keyboard::Right] = ACTION_CAMERA_TURN_RIGHT;
	keyboardActionMap[sf::Keyboard::Up] = ACTION_CAMERA_ZOOM_IN;
	keyboardActionMap[sf::Keyboard::Down] = ACTION_CAMERA_ZOOM_OUT;

	keyboardStateMap[sf::Keyboard::W] = STATE_CAMERA_RUNNING;

}

InputMapper::~InputMapper() {
	// TODO Auto-generated destructor stub
}

InputEvent* InputMapper::retrieveInputEvent() {
	currentInputEvent = new InputEvent(actionSet,stateSet);
	return currentInputEvent;
}

/**
 * This function takes the SFML Event and  creates the current InputEvent
 * out of the extracted data.
 */
void InputMapper::mapInputEvent(sf::Event event) {
	//TODO handle mouse input
	if (event.type == sf::Event::KeyPressed) {
		//States
		itKStateMap = keyboardStateMap.find(event.key.code);
		if (itKStateMap != keyboardStateMap.end())
			stateSet.insert(itKStateMap->second);
		else {
			//Actions
			itKActionMap = keyboardActionMap.find(event.key.code);
			if (itKActionMap != keyboardActionMap.end())
				actionSet.insert(itKActionMap->second);
		}

	} else if (event.type == sf::Event::KeyReleased) {  // Handle state release
		itKStateMap = keyboardStateMap.find(event.key.code);
		if (itKStateMap != keyboardStateMap.end()) {
			itStateSet = stateSet.find(itKStateMap->second);
			if (itKStateMap != keyboardStateMap.end())
				stateSet.erase(itStateSet);
		}
	}
}

