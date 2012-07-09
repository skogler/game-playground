/*
 * freemovementcam.hpp
 *
 *  Created on: Jun 18, 2012
 *      Author: zeheron
 */

#ifndef FREEMOVEMENTCAM_HPP_
#define FREEMOVEMENTCAM_HPP_

#include "../camera.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include "../../core/definitions.hpp"

class FreeMovementCam: public Camera
{
public:
	FreeMovementCam(shared_ptr<sf::RenderWindow> rwindow);
	virtual ~FreeMovementCam();

	virtual void handleinput(InputEvent* inputEvent);

protected:
	shared_ptr<sf::RenderWindow> window;
	int windowXhalf;
	int windowYhalf;
	void handleMouseMovement(int y, int x);
};

#endif /* FREEMOVEMENTCAM_HPP_ */
