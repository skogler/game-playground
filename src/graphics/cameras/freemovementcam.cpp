/*
 * freemovementcam.cpp
 *
 *  Created on: Jun 18, 2012
 *      Author: zeheron
 */

#include "freemovementcam.hpp"
#include "../graphics-definitions.hpp"
#include <SFML/Window/Mouse.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

FreeMovementCam::FreeMovementCam(shared_ptr<sf::Window> window) :
	window(window)
{
	windowXhalf = window->getSize().x / 2;
	windowYhalf = window->getSize().y / 2;
	sf::Mouse::setPosition(sf::Vector2<int>(windowXhalf, windowYhalf));
	window->setMouseCursorVisible(false);
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
	if (inputEvent.containsAction(ACTION_MOUSE_MOVED))
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
	rotateGlobal(vertMovement, UNIT_X);

	sf::Mouse::setPosition(sf::Vector2<int>(windowXhalf, windowYhalf), *window);
}
