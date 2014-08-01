/*
 * InputEvent.cpp
 *
 *  Created on: Jun 14, 2012
 *      Author: zeheron
 */

#include "inputevent.hpp"

InputEvent::InputEvent(std::set<Action>& actionSet,
                       std::set<State>&  stateSet,
                       bool              mouseMoved)
    : actionSet(actionSet)
    , stateSet(stateSet)
    , mouseMoved(mouseMoved)
{
}

InputEvent::~InputEvent()
{
}

bool InputEvent::containsAction(Action action)
{
    return actionSet.find(action) != actionSet.end();
}

bool InputEvent::containsState(State state)
{
    return stateSet.find(state) != stateSet.end();
}
