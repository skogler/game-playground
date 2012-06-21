/*
 * InputManager.hpp
 *
 *  Created on: Jun 10, 2012
 *      Author: zeheron
 */

#ifndef INPUTMANAGER_HPP_
#define INPUTMANAGER_HPP_

#include <SFML/Window/Event.hpp>
#include <list>
#include <iostream>
#include <boost/shared_ptr.hpp>

#include "inputlistener.hpp"

class InputManager
{

public:
	InputManager();
	virtual ~InputManager();
	void addListener(boost::shared_ptr<InputListener> listener);
	void removeListener(boost::shared_ptr<InputListener> listener);
	void handleUserInput(InputEvent *inEvent);

	//Getter and setter
	std::list< boost::shared_ptr<InputListener> > getListeners() const
	{
		return vListeners;
	}
private:
	std::list< boost::shared_ptr<InputListener> > vListeners;
};

#endif /* INPUTMANAGER_HPP_ */
