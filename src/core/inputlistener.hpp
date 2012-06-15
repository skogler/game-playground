/*
 * InputListener.hpp
 *
 *  Created on: Jun 10, 2012
 *      Author: zeheron
 */

#ifndef INPUTLISTENER_HPP_
#define INPUTLISTENER_HPP_

#include <SFML/Window/Event.hpp>
#include "inputevent.hpp"

class InputListener {

public:

	virtual void handleinput(InputEvent*inputEvent ) = 0;


	InputListener() {  }
	virtual ~InputListener() {  }

};

#endif /* INPUTLISTENER_HPP_ */
