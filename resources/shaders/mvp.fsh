#version 330

smooth in vec4 vertexColor;
out vec4 fragColor;

void main()
{
	fragColor = vertexColor;
}