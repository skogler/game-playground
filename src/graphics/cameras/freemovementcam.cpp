/*
 * freemovementcam.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: zeheron
 */

#include "../graphics-definitions.hpp"
#include "freemovementcam.hpp"
#include <iostream>

FreeMovementCam::FreeMovementCam()
{
}

FreeMovementCam::~FreeMovementCam()
{
}

/**
 * Handles the input events for the camera object.
 */
void FreeMovementCam::handleinput(InputEvent& inputEvent)
{
    if (inputEvent.containsState(STATE_CAMERA_MOVING_FORWARD))
    {
        moveForward(0.1);
    }
    if (inputEvent.containsState(STATE_CAMERA_MOVING_BACK))
    {
        moveForward(-0.1);
    }
    if (inputEvent.containsState(STATE_CAMERA_MOVE_RIGHT))
    {
        moveRight(0.1);
    }
    if (inputEvent.containsState(STATE_CAMERA_MOVE_LEFT))
    {
        moveRight(-0.1);
    }
    if (inputEvent.containsAction(ACTION_CAMERA_TURN_LEFT))
    {
        rotateY(-0.01f);
    }
    if (inputEvent.containsAction(ACTION_CAMERA_TURN_RIGHT))
    {
        rotateY(0.01f);
    }
    if (inputEvent.containsAction(ACTION_CAMERA_TURN_UP))
    {
        rotateX(0.05f);
    }
    if (inputEvent.containsAction(ACTION_CAMERA_TURN_DOWN))
    {
        rotateX(-0.05f);
    }
    if (inputEvent.mouseMoved)
    {
        static const float sensitivity   = 0.01f;
        float              horizMovement = -inputEvent.mouseMotionX *
                                           sensitivity;
        float vertMovement = -inputEvent.mouseMotionY *
                             sensitivity;

        rotateY(horizMovement);
        rotateGlobal(vertMovement, UNIT_X);
    }
}
