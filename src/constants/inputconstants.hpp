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
		ACTION_CAMERA_ZOOM_OUT,
		ACTION_CAMERA_ZOOM_IN

	};

	enum State
	{
		STATE_DEFAULT,
		STATE_PLAYER_RUNNING,
		STATE_CAMERA_RUNNING
	};



}


#endif /* INPUTCONSTANTS_HPP_ */