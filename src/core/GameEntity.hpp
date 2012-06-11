#ifndef GAMEENTITY_HPP_
#define GAMEENTITY_HPP_

#include "../utils/UIDGenerator.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GameEntity {
public:
	GameEntity();
	virtual ~GameEntity() {}

	virtual void update() = 0;

    inline int get_uid() const { return uid; }

    inline void set_movementSpeed(unsigned short movementSpeed) { this->movementSpeed = movementSpeed; }
    inline unsigned short get_movementSpeed() { return movementSpeed; }

    inline void set_turnSpeed(unsigned short turnSpeed) { this->turnSpeed = turnSpeed; }
    inline unsigned short get_turnSpeed() { return turnSpeed; }

    inline const glm::vec3& get_position() const { return position; }
    inline void set_position(glm::vec3& position) { this->position = position; }

    inline const glm::mat4& get_modelMatrix() const { return modelMatrix; }

    // Movement functions
    void move(float amount);
    void strafe(float amount);
    void turn(float amountHorizontal, float amountVertical);
    void lookAt(const glm::vec3& target);

protected:
	 int uid;

     float horizontalAngle;
     float verticalAngle;
     unsigned short movementSpeed;
     unsigned short turnSpeed;

     glm::mat4 modelMatrix;
     glm::vec3 position;
     glm::vec3 orientation;
     glm::vec3 orientationRight;
     glm::vec3 orientationUp;

     void updateValues();
};

#endif /* GAMEENTITY_HPP_ */
