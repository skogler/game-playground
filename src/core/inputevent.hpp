/*
 * InputEvent.hpp
 *
 *  Created on: Jun 14, 2012
 *      Author: zeheron
 */

#ifndef INPUTEVENT_HPP_
#define INPUTEVENT_HPP_
#include "constants/inputconstants.hpp"
#include <list>
#include <set>
using namespace input_constants;

class InputEvent final
{
private:
    std::set<Action>& actionSet;
    std::set<State>&  stateSet;

public:
    InputEvent(std::set<Action> &actionSet,
               std::set<State> &stateSet,
               bool mouseMoved);
    ~InputEvent();

    bool mouseMoved;
    int  mouseMotionX;
    int  mouseMotionY;

    bool containsAction(Action action);
    bool containsState(State state);



    void setStateSet(const std::set<State>& stateSet)
    {
        this->stateSet = stateSet;
    }

    void setActionSet(const std::set<Action>& actionSet)
    {
        this->actionSet = actionSet;
    }

    const std::set<Action>& getActionSet() const
    {
        return actionSet;
    }

    const std::set<State>& getStateSet() const
    {
        return stateSet;
    }
};

#endif /* INPUTEVENT_HPP_ */
