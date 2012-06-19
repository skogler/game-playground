#include "renderedentity.hpp"

RenderedEntity::RenderedEntity()
{
}

RenderedEntity::~RenderedEntity()
{
}

void RenderedEntity::render() const
{
	mesh->render();
}

void RenderedEntity::update()
{
}

