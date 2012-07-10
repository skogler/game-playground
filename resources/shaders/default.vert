#version 330 core
#pragma optionNV(unroll all)
#define MAX_LIGHTS 10

layout( location = 0) in vec3 position;
layout( location = 1) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

struct Light
{
	vec3 position;
	vec3 color;
	float intensity;
};

struct LightResult
{
	vec3 directionWorldSpace;
	float distance;
};

uniform int numLights;
uniform Light lights[MAX_LIGHTS];

out LightResult lightResults[MAX_LIGHTS];
out vec3 normalWorldSpace;

void main()
{
	vec4 posModelSpace = vec4(position, 1);
	vec4 posWorldSpace = modelMatrix * posModelSpace;
	gl_Position = projectionMatrix * viewMatrix * posWorldSpace;

	normalWorldSpace = normalize((modelMatrix * vec4(normal, 0)).xyz); // Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.

	for (int i = 0; i < MAX_LIGHTS; ++i)
	{
		// Vector that goes from the vertex to the Light
		lightResults[i].directionWorldSpace = normalize(posWorldSpace.xyz - lights[i].position);
		lightResults[i].distance = distance(posWorldSpace.xyz, lights[i].position);
	}
}
