#include "renderedentity.hpp"

RenderedEntity::RenderedEntity() :
		mesh(0)
{
}

RenderedEntity::~RenderedEntity()
{
	if (mesh != 0)
	{
		delete mesh;
	}
}

void RenderedEntity::render() const
{
	mesh->render();
}

void RenderedEntity::update()
{
}

