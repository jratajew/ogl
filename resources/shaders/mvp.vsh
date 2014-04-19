#version 330

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

smooth out vec4 vertexColor;

void main()
{
	gl_Position = projectionMatrix * modelViewMatrix * vec4( position, 1.0 );
	vertexColor = color;
}