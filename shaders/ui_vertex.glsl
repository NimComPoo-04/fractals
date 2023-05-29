#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 tex_coord;

uniform vec2 Position = vec2(0, 0);
uniform float Scale = 0.1;

out vec2 TexCoord;
out vec3 Color;

void main(void)
{
	gl_Position = vec4(position * Scale + Position, 1.0);
	TexCoord = tex_coord;
	Color = color;
}
