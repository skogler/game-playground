#ifndef RENDEREDENTITY_INC
#define RENDEREDENTITY_INC

#include "../core/gameentity.hpp"
#include "../core/resources/mesh.hpp"
#include "../core/definitions.hpp"

class RenderedEntity: public GameEntity
{
public:
	explicit RenderedEntity();
	virtual ~RenderedEntity();

	virtual void update();

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

