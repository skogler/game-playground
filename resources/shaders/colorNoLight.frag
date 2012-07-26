#version 330 core

// The fourth parameter for colors is intensity
struct Material
{
	vec4 diffuseColor;
	vec4 specularColor;
	float ambient;
};

uniform Material material;

out vec3 finalColor;

void main()
{
	finalColor = material.diffuseColor.rgb * material.diffuseColor.a; // a = intensity
}
