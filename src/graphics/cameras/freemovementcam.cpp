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

FreeMovementCam::FreeMovementCam(shared_ptr<sf::RenderWindow> window) :
				window(window)
{
	windowXhalf = window->getSize().x / 2;
	windowYhalf = window->getSize().y / 2;
	//sf::Mouse::setPosition(sf::Vector2<int>(windowXhalf, windowYhalf));
}

FreeMovementCam::~FreeMovementCam()
{
}

/**
 * Handles the input events for the camera object.
 */
void FreeMovementCam::handleinput(InputEvent* inputEvent)
{
	if (inputEvent->containsState(STATE_CAMERA_MOVING_FORWARD))
	{
		this->moveForward(0.3);
	}
	if (inputEvent->containsState(STATE_CAMERA_MOVING_BACK))
	{
		this->moveForward(-0.3);
	}
	if (inputEvent->containsState(STATE_CAMERA_MOVE_RIGHT))
	{
		this->moveRight(0.3);
	}
	if (inputEvent->containsState(STATE_CAMERA_MOVE_LEFT))
	{
		this->moveRight(-0.3);
	}
	if (inputEvent->containsAction(ACTION_CAMERA_TURN_LEFT))
	{
		this->rotateY(-0.05f);
	}
	if (inputEvent->containsAction(ACTION_CAMERA_TURN_RIGHT))
	{
		this->rotateY(0.05f);
	}
	if (inputEvent->containsAction(ACTION_CAMERA_TURN_UP))
	{
		this->rotateX(0.05f);
	}
	if (inputEvent->containsAction(ACTION_CAMERA_TURN_DOWN))
	{
		this->rotateX(-0.05f);
	}
	if (inputEvent->containsAction(ACTION_MOUSE_MOVED))
	{
		handleMouseMovement(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y);
	}
}

/**
 * Handles mouse position changes and converts them to camera movements.
 */
void FreeMovementCam::handleMouseMovement(int x, int y)
{
	float sensitivity = 0.001f;
	float horizMovement = (windowXhalf - x) * sensitivity;
	float vertMovement = (windowYhalf - y) * sensitivity;

	rotateY(horizMovement);
	rotateX(vertMovement);

	sf::Mouse::setPosition(sf::Vector2<int>(windowXhalf, windowYhalf), *window);
}
