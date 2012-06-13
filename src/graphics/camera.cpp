#include "camera.hpp"
#include "../core/gameentity.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera() :
		aspectRatio(1.3333f)
{
	projectionMatrix = glm::perspective(45.0f, aspectRatio, 0.1f, 100.0f);
}

Camera::~Camera()
{
}
