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

class FreeMovementCam: public Camera {
public:
	FreeMovementCam(sf::RenderWindow* rwindow);
	virtual ~FreeMovementCam();

	void handleinput(InputEvent*inputEvent );



protected:
	sf::RenderWindow* rwindow;
	float lastX;
	float lastY;
	int windowXhalf;
	int windowYhalf;
	void handleMouseMovement(int y, int x);
	void updateValues();

};

#endif /* FREEMOVEMENTCAM_HPP_ */
