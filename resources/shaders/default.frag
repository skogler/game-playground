#version 330 core

//uniform sampler2D texture0;

uniform vec4 diffuseColor;
//uniform vec4 specularColor;
//uniform vec4 ambientColor;
//uniform vec2 textureCoord;

out vec4 color;

void main()
{
    color = diffuseColor;// * texture(texture0, textureCoord).rgb;
}
