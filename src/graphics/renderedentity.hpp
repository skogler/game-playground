#ifndef RENDEREDENTITY_INC
#define RENDEREDENTITY_INC

#include "core/definitions.hpp"
#include "core/gameentity.hpp"
#include "core/resources/mesh.hpp"

class RenderedEntity : public GameEntity
{
public:
    explicit RenderedEntity();
    virtual ~RenderedEntity();

    inline void setMesh(const shared_ptr<Mesh> mesh)
    {
        this->mesh = mesh;
    }

    inline shared_ptr<Mesh> getMesh()
    {
        return mesh;
    }
protected:
    shared_ptr<Mesh> mesh;
};

#endif /* end of include guard: RENDEREDENTITY_INC */
