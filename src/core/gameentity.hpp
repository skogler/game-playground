#ifndef GAMEENTITY_HPP_
#define GAMEENTITY_HPP_

#include "utils/uidgenerator.hpp"
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

struct Transform
{
    float     scale;
    glm::quat rotation;
    glm::vec3 translation;
};

class GameEntity
{
public:
    GameEntity();
    virtual ~GameEntity()
    {
    }

    virtual void update();

    inline int getUid() const
    {
        return uid;
    }

    inline void setMovementSpeed(unsigned short movementSpeed)
    {
        this->movementSpeed = movementSpeed;
    }
    inline unsigned short getMovementSpeed()
    {
        return movementSpeed;
    }

    inline void setTurnSpeed(unsigned short turnSpeed)
    {
        this->turnSpeed = turnSpeed;
    }
    inline unsigned short getTurnSpeed()
    {
        return turnSpeed;
    }

    inline const glm::vec3& getPosition() const
    {
        return position;
    }

    inline void setPosition(glm::vec3& position)
    {
        this->position   = position;
        positionModified = true;
    }

    inline const glm::mat4& getModelMatrix()
    {
        return modelMatrix;
    }

    // Movement functions
    void moveForward(const float amount);
    void moveRight(const float amount);
    void moveUp(const float amount);
    void rotateX(const float angleRadians);
    void rotateY(const float angleRadians);
    void rotateZ(const float angleRadians);
    void lookAt(const glm::vec3& target);

    void rotateGlobal(const float angleRadians, const glm::vec3& axis);

protected:
    int  uid;
    bool positionModified;
    bool rotationModified;

    unsigned short movementSpeed;
    unsigned short turnSpeed;

    glm::mat4 modelMatrix;
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;
    glm::quat rotation;

    virtual void updateModelMatrix();
    virtual void updateDirections();
    void rotate(const float angleRadians, const glm::vec3& axis);
};

#endif /* GAMEENTITY_HPP_ */
