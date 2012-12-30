#version 330
#pragma optionNV(unroll all)
#define MAX_LIGHTS 10

//constant
vec3 ambientColor = vec3(0.1f, 0.1f, 0.1f);

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

// The fourth parameter for colors is intensity

struct Material
{
	vec4 diffuseColor;
	vec4 specularColor;
	float ambient;
};

uniform Material material;

uniform sampler2D texture;
uniform Light lights[MAX_LIGHTS];

// Interpolated calculation results from the vertex shader
in LightResult lightResults[MAX_LIGHTS];
in vec3 normalCameraSpace;
in vec3 eyeDirectionCameraSpace;

in vec2 textureCoordinatesFrag;

out vec3 finalColor;

void main()
{
	// Normalize vectors because they have been interpolated
	vec3 E = normalize(eyeDirectionCameraSpace);
	vec3 N = normalize(normalCameraSpace);

	vec3 diffuseLight = ambientColor;
	vec3 specularLight;
	float cosTheta = 0;
	float cosAlpha = 0;
	vec3 L;
	vec3 R;
	for (int i = 0; i < MAX_LIGHTS; ++i)
	{
		// Normalize light direction because it was interpolated for the fragment
		L = normalize(lightResults[i].directionCameraSpace);
		// Direction in which light is reflected
		R = reflect(-L, N);
		// Diffuse intensity => depends on angle to light
		cosTheta = clamp(dot(N, L), 0, 1);
		// Specular intensity => depends on angle of reflection to camera
		// 1 = camera is aligned to the reflection direction == show specular highlight
		cosAlpha = clamp(dot(E, R), 0, 1);

		float sqDistance = lightResults[i].distance * lightResults[i].distance;
		float attenuation = (1.0f + lights[i].linearAttenuation * lightResults[i].distance + lights[i].squaredAttenuation * sqDistance);
		// Add diffuse color
		diffuseLight += lights[i].intensity * lights[i].color * cosTheta / attenuation;
		// Add specular color
		specularLight += lights[i].color * (lights[i].intensity * pow(cosAlpha, 5)) / attenuation;
	}

	vec3 diffuseColor = texture2D(texture, textureCoordinatesFrag).rgb;

/**
	finalColor = diffuseColor * ambientColor  + diffuseColor * diffuseLight  + diffuseColor *
			specularLight; // a = intensity
			*/

	// DEBUG: show UV coordinates as red and green on models
	finalColor = vec3(textureCoordinatesFrag.x, textureCoordinatesFrag.y, 0.0f);

}
