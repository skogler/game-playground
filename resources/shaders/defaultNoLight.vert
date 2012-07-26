#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	vec4 posModelSpace = vec4(position, 1);
	vec4 posWorldSpace = modelMatrix * posModelSpace;
	vec4 positionCameraSpace = viewMatrix * posWorldSpace;
	gl_Position = projectionMatrix * positionCameraSpace;
}
