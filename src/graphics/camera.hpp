#ifndef CAMERA_INC
#define CAMERA_INC

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <GL/glew.h>

#include "core/gameentity.hpp"
#include "core/inputlistener.hpp"

/**
 * Provides an interface for a camera, extends entity and has a
 * position and orientation. Also provides the projection matrix
 * to be used in the shader.
 */
class Camera: public GameEntity , public InputListener
{
	public:
		Camera();
		virtual ~Camera();

		virtual void handleinput(InputEvent* inputEvent );
	protected:
		virtual void updateModelMatrix();
};

#endif /* end of include guard: CAMERA_INC */
