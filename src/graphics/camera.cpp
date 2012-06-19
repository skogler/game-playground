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


}
void Camera::updateValues()
{
	orientation = glm::vec3(cos(verticalAngle) * sin(horizontalAngle),
							sin(verticalAngle),
							cos(verticalAngle) * cos(horizontalAngle));
	orientationRight = glm::vec3(sin(horizontalAngle - 3.1415926f / 2.0f), 0, cos(horizontalAngle - 3.1415926f / 2.0f));
	orientationUp = glm::cross(orientationRight, orientation);

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::rotate(modelMatrix, -(horizontalAngle * 180.0f / 3.1415926f), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, -(verticalAngle * 180.0f / 3.1415926f), glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::translate(modelMatrix, position);
}
