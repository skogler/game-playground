/*
 * InputMapper.hpp
 *
 *  Created on: Jun 13, 2012
 *      Author: zeheron
 */

#ifndef INPUTMAPPER_HPP_
#define INPUTMAPPER_HPP_

#include "definitions.hpp"
#include "inputevent.hpp"
#include <SDL2/SDL.h>
#include <map>

class InputMapper
{
private:
    std::map<SDL_Keycode, Action> keyboardActionMap;
    std::map<SDL_Keycode, State>  keyboardStateMap;

    std::set<Action> actionSet;
    std::set<State>  stateSet;
    bool             mouseMoved;
    InputEvent       currentInputEvent;

    // Iterators
    decltype(keyboardActionMap)::iterator itKActionMap;
    decltype(keyboardStateMap)::iterator itKStateMap;
    decltype(stateSet)::iterator itStateSet;

public:
    InputMapper();
    virtual ~InputMapper();

    InputEvent& retrieveInputEvent();

    void mapInputEvent(SDL_Event& event);
    void endFrame();
};

#endif /* INPUTMAPPER_HPP_ */
