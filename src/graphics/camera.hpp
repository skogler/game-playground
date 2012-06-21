#ifndef CAMERA_INC
#define CAMERA_INC
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "../core/gameentity.hpp"
#include "../core/inputlistener.hpp"

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

	inline void set_aspectRatio(const float aspectRatio)
	{
		this->aspectRatio = aspectRatio;
	}
	inline const glm::mat4& get_projectionMatrix() const
	{
		return projectionMatrix;
	}

	virtual void handleinput(InputEvent* inputEvent );

protected:
	virtual void updateModelMatrix();
	float aspectRatio;
	float fov;
	glm::mat4 projectionMatrix;
};

#endif /* end of include guard: CAMERA_INC */
