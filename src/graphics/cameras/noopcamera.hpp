#ifndef NOOPCAMERA_HPP_
#define NOOPCAMERA_HPP_

#include "graphics/camera.hpp"

/**
 * Simple camera that always returns the identity matrix.
 * Basically like viewing everything in world space.
 */
class NoOpCamera: public Camera
{
	public:
		NoOpCamera();
		virtual ~NoOpCamera();

		virtual void handleinput(InputEvent* inputEvent ) {};
	protected:
		virtual void updateModelMatrix() {};
};

#endif /* NOOPCAMERA_HPP_ */
