#version 330

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

//attribute highp vec3 position;
//attribute highp vec4 color;

smooth out vec4 vertexColor;

void main()
{
	gl_Position = vec4( position, 1.0 );
	vertexColor = color;
}