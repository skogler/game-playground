/*
 * freemovementcam.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: zeheron
 */

#include "freemovementcam.hpp"
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

FreeMovementCam::FreeMovementCam(sf::RenderWindow* rwindow) {
	this->rwindow = rwindow;
	windowXhalf = rwindow->sf::Window::getSize().x / 2;
	windowYhalf = rwindow->sf::Window::getSize().y / 2;
	sf::Mouse::setPosition(sf::Vector2<int>(windowXhalf, windowYhalf),
			*rwindow);
}

FreeMovementCam::~FreeMovementCam() {
}

/**
 * Handles the input events for the camera object.
 */
void FreeMovementCam::handleinput(InputEvent* inputEvent) {
	if (inputEvent->containsState(STATE_CAMERA_MOVING_FORWARD)) {
		this->move(0.3);
	}
	if (inputEvent->containsState(STATE_CAMERA_MOVING_BACK)) {
		this->move(-0.3);
	}
	if (inputEvent->containsState(STATE_CAMERA_MOVE_RIGHT)) {
		this->strafe(0.3);
	}
	if (inputEvent->containsState(STATE_CAMERA_MOVE_LEFT)) {
		this->strafe(-0.3);
	}

	if (inputEvent->containsAction(ACTION_CAMERA_TURN_LEFT)) {
		this->turn(-0.1f, 0.0);
		std::cout << horizontalAngle << std::endl;
		int result = horizontalAngle * 180.0f / 3.1415926f;

	}

	if (inputEvent->containsAction(ACTION_CAMERA_TURN_RIGHT)) {
		this->turn(0.1f, 0.0);
		std::cout << horizontalAngle << std::endl;
		int result = horizontalAngle * 180.0f / 3.1415926f;

	}

	if (inputEvent->containsAction(ACTION_CAMERA_TURN_UP)) {
		this->turn(0.0, 0.1f);
		std::cout << verticalAngle << std::endl;
		int result = verticalAngle * 180.0f / 3.1415926f;

	}

	if (inputEvent->containsAction(ACTION_CAMERA_TURN_DOWN)) {
		this->turn(0.0, -0.1f);
		std::cout << verticalAngle << std::endl;
		int result = verticalAngle * 180.0f / 3.1415926f;

	}

	if (inputEvent->containsAction(ACTION_MOUSE_MOVED)) {
		handleMouseMovement(sf::Mouse::getPosition(*rwindow).x,
				sf::Mouse::getPosition(*rwindow).y);
	}

}

/**
 * Handles mouse position changes and converts them to camera movements.
 */
void FreeMovementCam::handleMouseMovement(int x, int y) {
	float sentitivity = 0.001f;
	float horizMovement = (x - windowXhalf) * sentitivity;
	float vertMovement = (y - windowYhalf) * sentitivity;
	/*
	 float xDegree = horizontalAngle * 180.0f / 3.1415926f;
	 float yDegree = verticalAngle * 180.0f / 3.1415926f;
	 std::cout << xDegree << " : " << yDegree << std::endl;

	 if (yDegree < -60.0f) {
	 yDegree = -60.0f;
	 verticalAngle = (yDegree * (3.141592654f / 180.0f));
	 }

	 // Limit looking down to vertically down
	 if (yDegree > 90.0f) {
	 yDegree = 90.0f;
	 verticalAngle = (yDegree * (3.141592654f / 180.0f));
	 }

	 // Looking left and right. Keep the angles in the range -180.0f
	 if (xDegree < -180.0f) {
	 xDegree += 360.0f;
	 horizontalAngle = (xDegree * (3.141592654f / 180.0f));
	 }

	 if (xDegree > 180.0f) {
	 xDegree -= 360.0f;
	 horizontalAngle = (xDegree * (3.141592654f / 180.0f));
	 }
	 */
	this->turn(horizMovement * (-1), vertMovement * (-1));
	sf::Mouse::setPosition(sf::Vector2<int>(windowXhalf, windowYhalf),
			*rwindow);

}

void FreeMovementCam::updateValues() {
	orientation = glm::vec3(cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));
	orientationRight = glm::vec3(sin(horizontalAngle - 3.1415926f / 2.0f), 0,
			cos(horizontalAngle - 3.1415926f / 2.0f));
	orientationUp = glm::cross(orientationRight, orientation);

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::rotate(modelMatrix,
			-(horizontalAngle * 180.0f / 3.1415926f),
			glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix,
			-(verticalAngle * 180.0f / 3.1415926f),
			glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::translate(modelMatrix, position);
}

