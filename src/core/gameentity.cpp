#include "gameentity.hpp"
#include <glm/glm.hpp>
GameEntity::GameEntity() :
		modelMatrix(1.0f), horizontalAngle(0.0f), verticalAngle(0.0f), movementSpeed(1), turnSpeed(1), position(0.0f, 0.0f, 0.0f), orientation(
				0.0f, 0.0f, 0.0f), orientationUp(0.0f, 0.0f, 0.0f), orientationRight(0.0f, 0.0f, 0.0f)
{
	uid = UIDGenerator::instance()->next();
	updateValues();
}

void GameEntity::move(float amount)
{
	position += orientation * amount * static_cast<float>(movementSpeed);
	updateValues();
}

void GameEntity::strafe(float amount)
{
	position += orientationRight * amount * static_cast<float>(movementSpeed);
	updateValues();
}

void GameEntity::turn(float amountHorizontal, float amountVertical)
{
	horizontalAngle += amountHorizontal;
	verticalAngle += amountVertical;
	updateValues();
}

void GameEntity::updateValues()
{
	orientation = glm::vec3(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));

	orientationRight = glm::vec3(sin(horizontalAngle - 3.1415926f / 2.0f), 0, cos(horizontalAngle - 3.1415926f / 2.0f));

	orientationUp = glm::cross(orientationRight, orientation);

	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::rotate(modelMatrix, horizontalAngle * 180.0f / 3.1415926f, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, verticalAngle * 180.0f / 3.1415926f, glm::vec3(1.0f, 0.0f, 0.0f));
}

void GameEntity::lookAt(const glm::vec3& target)
{
	//TODO: implement
}

