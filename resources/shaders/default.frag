#version 330 core
#pragma optionNV(unroll all)
#define MAX_LIGHTS 10

//uniform sampler2D texture0;
//uniform vec2 textureCoord;

vec3 ambientColor = vec3(0.4f, 0.4f, 0.4f);

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

uniform vec3 diffuseColor;
uniform Light lights[MAX_LIGHTS];

in LightResult lightResults[MAX_LIGHTS];
in vec3 normalWorldSpace;


out vec3 finalColor;

void main()
{
	vec3 lightColor = ambientColor;
	float cosTheta = 0;
	for (int i = 0; i < MAX_LIGHTS; ++i)
	{
		cosTheta = clamp(dot(normalWorldSpace, lightResults[i].directionWorldSpace), 0, 1);
		lightColor += lights[i].intensity * ((lights[i].color * cosTheta));
	}

	finalColor = diffuseColor * lightColor; // * texture(texture0, textureCoord).rgb;
}
