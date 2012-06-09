#ifndef CAMERA_INC
#define CAMERA_INC
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "../utils/definitions.hpp"

/**
 * Provides an interface for a camera, manages matrices and calculates an MVP matrix
 * that can be used in the global vertex shader.
 */
class Camera {
public:
    Camera ();
    virtual ~Camera ();

    void upload();
    void lookAt(const glm::vec3 target);

    inline glm::mat4 get_mvpMatrix() const { return mvpMatrix; }

    inline void set_aspectRatio(const float aspectRatio) { this->aspectRatio = aspectRatio; }
    inline void set_horizontalAngle(const float horizontalAngle) { this->horizontalAngle = horizontalAngle; }
    inline void set_verticalAngle(const float verticalAngle) { this->verticalAngle = verticalAngle; }
    inline void set_position(const glm::vec3 position) { this->position = position; }

protected:
    float aspectRatio;
    float horizontalAngle;
    float verticalAngle;
    glm::vec3 position;

    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    glm::mat4 mvpMatrix;

    GLuint mvpMatrixGLID;
};

#endif /* end of include guard: CAMERA_INC */
