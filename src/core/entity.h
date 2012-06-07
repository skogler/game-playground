#ifndef ENTITY_INC
#define ENTITY_INC

class Entity
{
public:
    Entity ();
    virtual ~Entity ();

private:
    int id;
    Vector3f position;
    Vector3f orientation;

};

#endif /* end of include guard: ENTITY_INC */
