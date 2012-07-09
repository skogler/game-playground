#version 330 core

layout(location = 0) in vec3 position;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;


uniform vec4 diffuseColor;

//in vec2 textureCoord;

void main()
{
    vec4 v = vec4(position, 1);
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * v;
}
