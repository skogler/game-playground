/*
 * InputMapper.hpp
 *
 *  Created on: Jun 13, 2012
 *      Author: zeheron
 */

#ifndef INPUTMAPPER_HPP_
#define INPUTMAPPER_HPP_

#include <map>
#include <SFML/Window/Event.hpp>
#include "inputevent.hpp"
#include "definitions.hpp"

class InputMapper {

	private:
		std::map<sf::Keyboard::Key, Action> keyboardActionMap;
		std::map<sf::Keyboard::Key, State> keyboardStateMap;

		std::set<Action> actionSet;
		std::set<State> stateSet;
		bool mouseMoved;
		InputEvent* currentInputEvent;

		//Iterators
		std::map<sf::Keyboard::Key, Action>::iterator itKActionMap;
		std::map<sf::Keyboard::Key, State>::iterator itKStateMap;
		std::set<State>::iterator itStateSet;


	public:
		InputMapper();
		virtual ~InputMapper();

		InputEvent* retrieveInputEvent();

		void mapInputEvent(sf::Event event);
};

#endif /* INPUTMAPPER_HPP_ */
