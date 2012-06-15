/*
 * InputEvent.hpp
 *
 *  Created on: Jun 14, 2012
 *      Author: zeheron
 */

#ifndef INPUTEVENT_HPP_
#define INPUTEVENT_HPP_
#include "../constants/inputconstants.hpp"
#include <list>
#include <set>
using namespace input_constants;

class InputEvent {

private:
	std::set<Action> actionSet;
	std::set<State> stateSet;
	//Iterators
	std::set<Action>::iterator itActionSet;
	std::set<State>::iterator itStateSet;

public:
	InputEvent(std::set<Action> actionSet,std::set<State> stateSet);
	virtual ~InputEvent();

	bool containsAction(Action action);
	bool containsState(State state);

	void setStateSet(std::set<State> stateSet) {
		this->stateSet = stateSet;
	}

	void setActionSet(std::set<Action> actionSet) {
		this->actionSet = actionSet;
	}

	std::set<Action> getActionSet() const {
		return actionSet;
	}

	std::set<State> getStateSet() const {
		return stateSet;
	}
};

#endif /* INPUTEVENT_HPP_ */
