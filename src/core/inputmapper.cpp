/*
 * InputMapper.cpp
 *
 *  Created on: Jun 13, 2012
 *      Author: zeheron
 */

#include "inputmapper.hpp"

InputMapper::InputMapper()
    : keyboardActionMap()
    , keyboardStateMap()
    , actionSet()
    , stateSet()
    , mouseMoved(false)
    , currentInputEvent{actionSet, stateSet, mouseMoved}
{
    // TODO: Refactor this  so the assignments are read from a config file.
    keyboardActionMap[SDLK_a] = ACTION_CAMERA_MOVE_LEFT;
    keyboardActionMap[SDLK_d] = ACTION_CAMERA_MOVE_RIGHT;

    keyboardActionMap[SDLK_RIGHT] = ACTION_CAMERA_TURN_RIGHT;
    keyboardActionMap[SDLK_LEFT]  = ACTION_CAMERA_TURN_LEFT;
    keyboardActionMap[SDLK_UP]    = ACTION_CAMERA_TURN_UP;
    keyboardActionMap[SDLK_DOWN]  = ACTION_CAMERA_TURN_DOWN;

    // Important
    keyboardStateMap[SDLK_w] = STATE_CAMERA_MOVING_FORWARD;
    keyboardStateMap[SDLK_s] = STATE_CAMERA_MOVING_BACK;
    keyboardStateMap[SDLK_a] = STATE_CAMERA_MOVE_LEFT;
    keyboardStateMap[SDLK_d] = STATE_CAMERA_MOVE_RIGHT;
}

InputMapper::~InputMapper()
{
}

InputEvent& InputMapper::retrieveInputEvent()
{
    return currentInputEvent;
}

/**
 * This function takes the SDL Event and  creates the current InputEvent
 * out of the extracted data.
 */
void InputMapper::mapInputEvent(SDL_Event& event)
{
    // TODO handle mouse input
    if (event.type == SDL_KEYDOWN)
    {
        // States
        itKStateMap = keyboardStateMap.find(event.key.keysym.sym);
        if (itKStateMap != keyboardStateMap.end())
        {
            stateSet.insert(itKStateMap->second);
        }
        else
        {
            // Actions
            itKActionMap = keyboardActionMap.find(event.key.keysym.sym);
            if (itKActionMap != keyboardActionMap.end())
            {
                actionSet.insert(itKActionMap->second);
            }
        }
    }
    else if (event.type == SDL_KEYUP)
    {   // Handle state release
        itKStateMap = keyboardStateMap.find(event.key.keysym.sym);
        if (itKStateMap != keyboardStateMap.end())
        {
            itStateSet = stateSet.find(itKStateMap->second);
            if (itKStateMap != keyboardStateMap.end())
            {
                stateSet.erase(itStateSet);
            }
        }
    }
    if (event.type == SDL_MOUSEMOTION)
    {
        actionSet.insert(ACTION_MOUSE_MOVED);
        currentInputEvent.mouseMoved   = true;
        currentInputEvent.mouseMotionX = static_cast<int>(event.motion.xrel);
        currentInputEvent.mouseMotionY = static_cast<int>(event.motion.yrel);
    }
}

void InputMapper::endFrame()
{
    currentInputEvent.mouseMoved   = false;
    currentInputEvent.mouseMotionX = 0;
    currentInputEvent.mouseMotionY = 0;
    actionSet.clear();
}
