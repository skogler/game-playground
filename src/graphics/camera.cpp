#include "camera.hpp"
#include "../core/gameentity.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../constants/inputconstants.hpp"
#include <iostream>

#define PI 3.1415926f

Camera::Camera() :
				aspectRatio(1.3333f),
				fov(60.0f)
{
	projectionMatrix = glm::perspective(fov, aspectRatio, 0.1f, 1000.0f);
}

Camera::~Camera()
{
}

void Camera::handleinput(InputEvent* inputEvent)
{

}

void Camera::updateModelMatrix()
{
	// CAMERA: rotate and translate world with negative values
	modelMatrix = glm::transpose(glm::mat4_cast(rotation));
	modelMatrix = glm::translate(modelMatrix, -position);
	positionModified = false;
}
