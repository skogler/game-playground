#include "camera.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using glm::mat4;
using glm::vec3;

Camera::Camera() :
    aspectRatio(16.0f/9.0f),
    horizontalAngle(0),
    verticalAngle(0),
    mvpMatrixGLID(0)
{

}

Camera::~Camera()
{

}

void Camera::lookAt(const glm::vec3 target)
{

}

void Camera::upload()
{

}
