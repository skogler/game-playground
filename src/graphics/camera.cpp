#include "camera.hpp"
#include "../core/gameentity.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../constants/inputconstants.hpp"

Camera::Camera() :
		aspectRatio(1.3333f) {
	projectionMatrix = glm::perspective(45.0f, aspectRatio, 0.1f, 100.0f);
}

Camera::~Camera() {
}

void Camera::handleinput(InputEvent* inputEvent) {
	if (inputEvent->containsAction(ACTION_CAMERA_MOVE_LEFT)) {
		this->move(10.1);
	}
	if (inputEvent->containsAction(ACTION_CAMERA_MOVE_RIGHT)) {
		this->move(-10.1);
	}
	if (inputEvent->containsAction(ACTION_CAMERA_TURN_RIGHT)) {
		this->turn(-12.0,0);
	}
	if (inputEvent->containsAction(ACTION_CAMERA_TURN_LEFT)) {
		this->turn(12.0,0);
	}

}

