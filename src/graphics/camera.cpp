#include "camera.hpp"

#include "constants/inputconstants.hpp"
#include "core/gameentity.hpp"
#include "core/inputlistener.hpp"
#include "utils/logger.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#define PI 3.1415926f

Camera::Camera()
{
    updateModelMatrix();
}

Camera::~Camera()
{
}

void Camera::handleinput(InputEvent& inputEvent)
{
}

void Camera::updateModelMatrix()
{
    // CAMERA: rotate and translate world with negative values
    modelMatrix      = glm::transpose(glm::mat4_cast(rotation));
    modelMatrix      = glm::translate(modelMatrix, -position);
    positionModified = false;
}
