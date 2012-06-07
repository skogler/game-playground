#ifndef CAMERA_INC
#define CAMERA_INC
#include <glm/glm.hpp>
#include "../utils/definitions.hpp"

class Camera {
public:
    Camera ();
    virtual ~Camera ();

    inline void setAspectRatio(const float aspectRatio);
    inline void setHorizontalAngle(const float horizontalAngle);
    inline void setVerticalAngle(const float verticalAngle);
    inline void setPosition(const glm::vec3 position);

    inline glm::mat4 getMVPMatrix() const { return mvpMatrix; }

private:
    float aspectRatio;
    float horizontalAngle;
    float verticalAngle;
    glm::vec3 position;

    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    glm::mat4 mvpMatrix;
};

#endif /* end of include guard: CAMERA_INC */
