#include "camera.hpp"
#include "../core/gameentity.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../constants/inputconstants.hpp"
#include <iostream>

Camera::Camera() :
		aspectRatio(1.3333f) {
	projectionMatrix = glm::perspective(45.0f, aspectRatio, 0.1f, 100.0f);
}

Camera::~Camera() {
}

void Camera::handleinput(InputEvent* inputEvent) {
	if (inputEvent->containsState(STATE_CAMERA_MOVING_FORWARD)) {
		this->move(0.3);
	}
	if (inputEvent->containsState(STATE_CAMERA_MOVING_BACK)) {
		this->move(-0.3);
	}
	if (inputEvent->containsAction(ACTION_CAMERA_TURN_RIGHT)) {
		this->turn(0.3, 0);
	}
	if (inputEvent->containsAction(ACTION_CAMERA_TURN_LEFT)) {
		this->turn(-0.3, 0);
	}
	if (inputEvent->containsState(STATE_CAMERA_MOVE_RIGHT)) {
		this->strafe(-0.3);
	}
	if (inputEvent->containsState(STATE_CAMERA_MOVE_LEFT)) {
		this->strafe(0.3);
	}

}



