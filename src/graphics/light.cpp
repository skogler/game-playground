#include "light.hpp"

Light::Light(glm::vec3 position) :
    position(position),
    color(1.0f),
    intensity(0.5f),
    linearAttenuation(0.05f),
    squaredAttenuation(0.00f)
{
}

Light::~Light()
{
}
