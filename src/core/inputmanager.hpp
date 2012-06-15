/*
 * InputManager.hpp
 *
 *  Created on: Jun 10, 2012
 *      Author: zeheron
 */

#ifndef INPUTMANAGER_HPP_
#define INPUTMANAGER_HPP_

#include <SFML/Window/Event.hpp>
#include "inputlistener.hpp"
#include <list>
#include <iostream>

class InputManager {

private:
	InputManager();
	virtual ~InputManager();
	static InputManager *imInstance;
	std::list<InputListener*> vListeners;

public:
	static InputManager* instance();
	void addListener(InputListener* listener);
	void removeListener(InputListener* listener);
	void handleUserInput(InputEvent *inEvent);


	//Getter and setter
	std::list<InputListener*> getListeners() const {
		return vListeners;
	}

};

#endif /* INPUTMANAGER_HPP_ */
