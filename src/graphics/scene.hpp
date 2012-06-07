#ifndef SCENE_INC
#define SCENE_INC
#include <list>
#include <string>
using namespace std;

class Scene
{
public:
    Scene ();
    virtual ~Scene ();

    inline list<Entity>& getEntities()
    {
        return &entities;
    }

private:
    string name;
    list<Entity> entities;
};

#endif /* end of include guard: SCENE_INC */
