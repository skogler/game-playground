/*
 * InputEvent.cpp
 *
 *  Created on: Jun 14, 2012
 *      Author: zeheron
 */

#include "inputevent.hpp"

	InputEvent::InputEvent(std::set<Action> actionSet, std::set<State> stateSet, bool mouseMoved)
: actionSet(actionSet),
	stateSet(stateSet),
	mouseMoved(mouseMoved)
{
}

InputEvent::~InputEvent() {
	// TODO Auto-generated destructor stub
}

bool InputEvent::containsAction(Action action) {
	if (actionSet.find(action) != actionSet.end())
		return true;
	else
		return false;

}

bool InputEvent::containsState(State state) {
	if (stateSet.find(state) != stateSet.end())
		return true;
	else
		return false;

}

