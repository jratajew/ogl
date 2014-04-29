#version 330

struct DirectionalLight
{
	vec4 Ambient;
	vec4 Diffuse;
	vec4 Specular;
	vec3 Direction;
};

uniform DirectionalLight g_DirLight;

smooth in vec4 vertexColor;
smooth in vec3 mvPosition;
smooth in vec3 pixelNormal;

out vec4 fragColor;

void main()
{
	// Light:
	vec3 L = vec3(0.0, 1.0, 0.0);//-g_DirLight.Direction;
	vec4 D = vec4(0.8, 0.8, 0.8, 1.0);
	vec3 N = normalize(pixelNormal);
	vec4 diffuseFactor = D * max(dot(N,L), 0.0);
	diffuseFactor = clamp(diffuseFactor, 0.0, 1.0);

	fragColor = diffuseFactor;
}