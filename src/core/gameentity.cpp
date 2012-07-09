#include "gameentity.hpp"

#include "../graphics/graphics-definitions.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <iostream>
using std::cout;
using std::endl;

#define PI 3.1415926f

GameEntity::GameEntity() :
				modelMatrix(1.0f),
				movementSpeed(3),
				turnSpeed(1),
				position(0.0f, 0.0f, 0.0f),
				positionModified(false),
				rotationModified(false),
				front(-UNIT_Z),
				right(UNIT_X),
				up(UNIT_Y),
				rotation(0.0f, 0.0f, 0.0f, 1.0f) // = no-op rotation quaternion
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
	rotation = glm::rotate(rotation, glm::degrees(angleRadians), axis);
	rotation = glm::normalize(rotation);
	rotationModified = true;
}

void GameEntity::update()
{
	if (positionModified || rotationModified)
	{
		updateModelMatrix();
	}
	if(rotationModified)
	{
		updateDirections();
	}
}

void GameEntity::updateModelMatrix()
{
	// Apply translation first, then rotation (matrix multiplication)
	modelMatrix = glm::mat4_cast(rotation);
	modelMatrix = glm::translate(modelMatrix, position);
	positionModified = false;
}

void GameEntity::lookAt(const glm::vec3& target)
{
	//TODO: implement properly
	modelMatrix = glm::lookAt(position, target, glm::vec3(0.0f, 1.0f, 0.0f));
}

void GameEntity::updateDirections()
{
	front = rotation * (-UNIT_Z);
	right = glm::cross(front, up);  // UP is always the Y axis
	rotationModified = false;
}

