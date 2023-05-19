#version 330 core

precision highp float;

layout (location = 0) in vec3 position;
out vec2 coordinates;

uniform vec2 ratio;		// send in the normalized stuff
uniform vec2 scale;		// scaling factor
uniform vec2 center;

void main(void)
{
	coordinates = position.xy * ratio / scale + center * 2;
	gl_Position = vec4(position, 1.0);
}
