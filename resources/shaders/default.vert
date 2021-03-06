#version 330
#pragma optionNV(unroll all)
#define MAX_LIGHTS 1

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 textureCoordinates;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

struct Light
{
	vec3 position;
	vec3 color;
	float intensity;
	float linearAttenuation;
	float squaredAttenuation;
};

struct LightResult
{
	vec3 directionCameraSpace;
	float distance;
};

uniform int numLights;
uniform Light lights[MAX_LIGHTS];

// Light calculation results in camera space
out LightResult lightResults[MAX_LIGHTS];
out vec3 normalCameraSpace;
out vec3 eyeDirectionCameraSpace;

out vec2 textureCoordinatesFrag;

void main()
{
	vec4 posModelSpace = vec4(position, 1);
	vec4 posWorldSpace = modelMatrix * posModelSpace;
	vec4 positionCameraSpace = viewMatrix * posWorldSpace;
	gl_Position = projectionMatrix * positionCameraSpace;

	normalCameraSpace = (viewMatrix * modelMatrix * vec4(normal, 0)).xyz; // Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.

	eyeDirectionCameraSpace = vec3(0,0,0) - positionCameraSpace.xyz;

	for (int i = 0; i < MAX_LIGHTS; ++i)
	{
		vec4 lightPositionCameraSpace = viewMatrix * vec4(lights[i].position, 1);
		// Vector that goes from the vertex to the Light
		lightResults[i].directionCameraSpace = lightPositionCameraSpace.xyz + eyeDirectionCameraSpace;
		lightResults[i].distance = distance(positionCameraSpace, lightPositionCameraSpace);
	}
	
	textureCoordinatesFrag = textureCoordinates;
}
