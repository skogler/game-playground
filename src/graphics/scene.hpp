#ifndef SCENE_INC
#define SCENE_INC
#include <list>
#include <string>
#include "camera.hpp"
#include "mesh.hpp"
#include "RenderedEntity.hpp"

class Scene
{
public:
    explicit Scene (Camera * camera);
    virtual ~Scene ();

    void render() const;

    inline std::list<RenderedEntity*>& getEntities()
    {
        return entities;
    }

private:
    Camera * camera;
    std::string name;
    std::list<RenderedEntity *> entities;

    GLuint modelMatrix;
    GLuint viewMatrix;
    GLuint projectionMatrix;

    glm::mat4 vm;
    glm::mat4 mm;
};

#endif /* end of include guard: SCENE_INC */
