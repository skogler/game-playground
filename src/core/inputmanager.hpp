/*
 * InputManager.hpp
 *
 *  Created on: Jun 10, 2012
 *      Author: zeheron
 */

#ifndef INPUTMANAGER_HPP_
#define INPUTMANAGER_HPP_

#include "definitions.hpp"
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <list>

#include "inputlistener.hpp"

class InputManager
{
public:
    InputManager();
    virtual ~InputManager();
    void addListener(shared_ptr<InputListener> listener);
    void removeListener(shared_ptr<InputListener> listener);
    void handleUserInput(InputEvent& inEvent);

    // Getter and setter
    std::list<shared_ptr<InputListener> > getListeners() const
    {
        return vListeners;
    }
private:
    std::list<shared_ptr<InputListener> > vListeners;
};

#endif /* INPUTMANAGER_HPP_ */
