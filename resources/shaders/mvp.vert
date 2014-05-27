#version 430

uniform mat4 g_ProjectionMatrix;
uniform mat4 g_ModelViewMatrix;

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

//smooth out vec4 vertexColor;
//smooth out vec3 mvPosition;
//smooth out vec3 pixelNormal;

out VS_OUT
{
	vec2 texCoord;
	vec3 normal;
} vs_out;

void main()
{
	//mvPosition = (g_ModelViewMatrix * vec4( position, 1.0 )).xyz;
	//gl_Position = g_ModelViewMatrix * g_ProjectionMatrix * vec4( position, 1.0 );
	gl_Position = g_ProjectionMatrix * g_ModelViewMatrix * vec4( position, 1.0 );
	//vertexColor = vec4( 0.1, 0.8, 0.8, 1.0 );
	
	vs_out.normal = normal;
	vs_out.texCoord = texCoord;
}