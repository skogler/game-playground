/*
 * freemovementcam.hpp
 *
 *  Created on: Jun 18, 2012
 *      Author: zeheron
 */

#ifndef FREEMOVEMENTCAM_HPP_
#define FREEMOVEMENTCAM_HPP_

#include "graphics/camera.hpp"
#include <SFML/Window.hpp>
#include "core/definitions.hpp"

class FreeMovementCam: public Camera
{
	public:
		FreeMovementCam(shared_ptr<sf::Window> rwindow);
		virtual ~FreeMovementCam();

		virtual void handleinput(InputEvent* inputEvent);

	protected:
		shared_ptr<sf::Window> window;
		int windowXhalf;
		int windowYhalf;
		void handleMouseMovement(int y, int x);
};

#endif /* FREEMOVEMENTCAM_HPP_ */
