#include "light.hpp"

Light::Light(glm::vec3 position) :
	position(position),
	color(1.0f),
	intensity(0.5f)
{
}

Light::~Light()
{
}

