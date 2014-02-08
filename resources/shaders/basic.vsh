attribute highp vec3 position;
attribute highp vec4 color;

varying highp vec4 vertexColor;

void main()
{
	gl_Position = vec4( position, 1.0 );
	vertexColor = color;
}