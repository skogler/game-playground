#ifndef SCENE_INC
#define SCENE_INC
#include <list>
#include <string>
#include "../core/GameEntity.hpp"
using namespace std;

class Scene
{
public:
    Scene ();
    virtual ~Scene ();


    inline list<GameEntity>& getEntities() const
    {
        return &entities;
    }

private:
    string name;
    list<GameEntity> entities;
};

#endif /* end of include guard: SCENE_INC */
