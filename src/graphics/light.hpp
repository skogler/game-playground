#ifndef LIGHT_HPP_
#define LIGHT_HPP_

#include <glm/glm.hpp>

class Light
{
public:
	Light(glm::vec3 position);
	virtual ~Light();

	float getLinearAttenuation() const
	{
		return linearAttenuation;
	}

	void setLinearAttenuation(float linearAttenuation)
	{
		this->linearAttenuation = linearAttenuation;
	}

	float getSquaredAttenuation() const
	{
		return squaredAttenuation;
	}

	void setSquaredAttenuation(float squaredAttenuation)
	{
		this->squaredAttenuation = squaredAttenuation;
	}

	float getIntensity() const
	{
		return intensity;
	}

	void setIntensity(float intensity)
	{
		this->intensity = intensity;
	}

	glm::vec3 getColor() const
	{
		return color;
	}

	void setColor(glm::vec3 color)
	{
		this->color = color;
	}

	const glm::vec3& getPosition() const
	{
		return position;
	}

	void setPosition(glm::vec3& position)
	{
		this->position = position;
	}

protected:
	glm::vec3 position;
	glm::vec3 color;
	float intensity;
	float linearAttenuation;
	float squaredAttenuation;
};

#endif /* LIGHT_HPP_ */
