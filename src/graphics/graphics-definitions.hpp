#ifndef GRAPHICS_DEFINITIONS_HPP_
#define GRAPHICS_DEFINITIONS_HPP_

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "core/resources/material.hpp"

const glm::vec3 UNIT_X(1.0f, 0.0f, 0.0f);
const glm::vec3 UNIT_Y(0.0f, 1.0f, 0.0f);
const glm::vec3 UNIT_Z(0.0f, 0.0f, 1.0f);

const glm::mat4 IDENTITY_MATRIX(1.0f);

#define BUFFER_OFFSET(i) (reinterpret_cast<void*>(i))

#endif /* GRAPHICS_DEFINITIONS_HPP_ */
