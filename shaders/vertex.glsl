#version 330 core

layout (location = 0) in vec3 Position;

uniform vec2 Scale;
uniform vec2 Center;
uniform ivec2 ScreenSize;

out vec2 Coordinate;

void main(void)
{
	gl_Position = vec4(Position, 1.0);

	vec2 aspect_ratio = vec2(1.0, -1.0);
	
	if(ScreenSize.x > ScreenSize.y)
		aspect_ratio.x *= float(ScreenSize.x) / float(ScreenSize.y);
	else
		aspect_ratio.y *= float(ScreenSize.y) / float(ScreenSize.x);

	Coordinate = Position.xy * aspect_ratio / Scale + Center;
}
