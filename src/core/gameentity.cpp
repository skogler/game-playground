#include "gameentity.hpp"

#include "graphics/graphics-definitions.hpp"
#include "utils/logger.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <iostream>
using std::cout;
using std::endl;

#define PI 3.1415926f

GameEntity::GameEntity() :
				positionModified(true),
				rotationModified(true),
				movementSpeed(1),
				turnSpeed(1),
				modelMatrix(1.0f),
				position(0.0f, 0.0f, 0.0f),
				front(-UNIT_Z),
				right(UNIT_X),
				up(UNIT_Y),
				rotation(1.0f, 0.0f, 0.0f, 0.0f) // = no-op rotation quaternion
{
	uid = UIDGenerator::instance()->next();
	updateModelMatrix();
}

void GameEntity::moveForward(float amount)
{
	if (rotationModified)
	{
		updateDirections();
	}
	position += front * amount * static_cast<float>(movementSpeed);
	positionModified = true;
}

void GameEntity::moveRight(float amount)
{
	if (rotationModified)
	{
		updateDirections();
	}
	position += right * amount * static_cast<float>(movementSpeed);
	positionModified = true;
}

void GameEntity::moveUp(float amount)
{
	if (rotationModified)
	{
		updateDirections();
	}
	position += up * amount * static_cast<float>(movementSpeed);
	positionModified = true;
}

void GameEntity::rotateX(const float angleRadians)
{
	rotate(angleRadians, UNIT_X);
}

void GameEntity::rotateY(const float angleRadians)
{
	rotate(angleRadians, UNIT_Y);
}

void GameEntity::rotateZ(const float angleRadians)
{
	rotate(angleRadians, UNIT_Z);
}

void GameEntity::rotate(const float angleRadians, const glm::vec3 & axis)
{
//	rotation = glm::rotate(rotation, glm::degrees(angleRadians), axis);
  glm::quat mod_rot = glm::angleAxis(glm::degrees(angleRadians), axis);
  rotation = mod_rot * rotation;
	rotation = glm::normalize(rotation);
	rotationModified = true;
}

void GameEntity::rotateGlobal(const float angleRadians, const glm::vec3 & axis)
{
//	rotation = glm::rotate(rotation, glm::degrees(angleRadians), axis);
//	rotation = glm::normalize(rotation);
  glm::quat mod_rot = glm::angleAxis(glm::degrees(angleRadians), axis);
  rotation = rotation * mod_rot ;
	rotationModified = true;
}
void GameEntity::update()
{
	if (positionModified || rotationModified)
	{
		updateModelMatrix();
	}
	if (rotationModified)
	{
		updateDirections();
	}
}

void GameEntity::updateModelMatrix()
{
	// Apply translation first, then rotation
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = modelMatrix * glm::mat4_cast(rotation);
	positionModified = false;
}

void GameEntity::lookAt(const glm::vec3& target)
{
	//TODO: implement properly
	modelMatrix = glm::lookAt(position, target, glm::vec3(0.0f, 1.0f, 0.0f));
	rotation = glm::quat_cast(modelMatrix);
	updateDirections();
}

void GameEntity::updateDirections()
{
	front = rotation * (-UNIT_Z);
	right = rotation * (UNIT_X);
	up = rotation * (UNIT_Y);
	rotationModified = false;
}

