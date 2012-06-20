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
	/*
	sf::Mouse::setPosition(sf::Vector2<int>(windowXhalf, windowYhalf),
			*rwindow);
*/
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
	if (inputEvent->containsAction(ACTION_MOUSE_MOVED)) {
		handleMouseMovement(sf::Mouse::getPosition(*rwindow).x,
				sf::Mouse::getPosition(*rwindow).y);
	}

}

/**
 * Handles mouse position changes and converts them to camera movements.
 */
void FreeMovementCam::handleMouseMovement(int y, int x) {
	turnSpeed = 0.1f;
	float sensitivity = 1000.0f;
	float horizMovement = x - windowXhalf;
	float vertMovement = y - windowYhalf;
	horizMovement = horizMovement/sensitivity;
	vertMovement = vertMovement/sensitivity;

	std::cout << horizMovement << std::endl;
			std::cout << vertMovement << std::endl;
	this->turn(horizMovement, vertMovement);
	//horizontalAngle += vertMovement / ySensitivity;
	//verticalAngle += horizMovement / xSensitivity;

	/* sf::Mouse::setPosition(sf::Vector2<int>(windowXhalf, windowYhalf),
			*rwindow);
		*/
}

