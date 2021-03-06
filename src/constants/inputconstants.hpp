/*
 * inputconstants.hpp
 *
 *  Created on: Jun 13, 2012
 *      Author: zeheron
 */

#ifndef INPUTCONSTANTS_HPP_
#define INPUTCONSTANTS_HPP_

namespace input_constants
{
enum Action
{
    ACTION_DEFAULT,
    ACTION_CAMERA_MOVE_LEFT,
    ACTION_CAMERA_MOVE_RIGHT,
    ACTION_CAMERA_TURN_LEFT,
    ACTION_CAMERA_TURN_RIGHT,
    ACTION_CAMERA_TURN_UP,
    ACTION_CAMERA_TURN_DOWN,

    // Mouse
    ACTION_MOUSE_MOVED
};

enum State
{
    STATE_DEFAULT,
    STATE_PLAYER_RUNNING,
    // Camera
    STATE_CAMERA_MOVING_FORWARD,
    STATE_CAMERA_MOVING_BACK,
    STATE_CAMERA_MOVE_LEFT,
    STATE_CAMERA_MOVE_RIGHT,

    // Mouse
};
}


#endif /* INPUTCONSTANTS_HPP_ */
