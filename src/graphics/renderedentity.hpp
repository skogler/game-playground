#ifndef RENDEREDENTITY_INC
#define RENDEREDENTITY_INC

#include "../core/gameentity.hpp"
#include "mesh.hpp"

class RenderedEntity: public GameEntity
{
public:
	explicit RenderedEntity();
	virtual ~RenderedEntity();

	virtual void render() const;
	virtual void update();
	inline void set_mesh(Mesh * mesh)
	{
		this->mesh = mesh;
	}
protected:
	Mesh * mesh;
};

#endif /* end of include guard: RENDEREDENTITY_INC */

