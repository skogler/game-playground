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
#include <boost/shared_ptr.hpp>

class FreeMovementCam: public Camera {
public:
	FreeMovementCam(boost::shared_ptr<sf::RenderWindow> rwindow);
	virtual ~FreeMovementCam();

	virtual void handleinput(InputEvent* inputEvent );

protected:
	boost::shared_ptr<sf::RenderWindow> window;
	int windowXhalf;
	int windowYhalf;
	void handleMouseMovement(int y, int x);

};

#endif /* FREEMOVEMENTCAM_HPP_ */
