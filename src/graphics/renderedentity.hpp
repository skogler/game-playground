#ifndef RENDEREDENTITY_INC
#define RENDEREDENTITY_INC

#include "../core/gameentity.hpp"
#include "resources/mesh.hpp"
#include <boost/shared_ptr.hpp>

class RenderedEntity: public GameEntity
{
public:
	explicit RenderedEntity();
	virtual ~RenderedEntity();

	virtual void render() const;
	virtual void update();
	inline void set_mesh(const boost::shared_ptr<Mesh> mesh)
	{

		this->mesh = mesh;
	}
protected:
	boost::shared_ptr<Mesh> mesh;
};

#endif /* end of include guard: RENDEREDENTITY_INC */

