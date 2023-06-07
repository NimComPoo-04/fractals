#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texcoord;
// layout (location = 2) in vec2 pos;

uniform ivec2 ScreenSize;
uniform vec2 Translate;

out vec2 TexCoord;
out vec4 Color;

void main(void)
{
	vec2 aspect_ratio = vec2(1.0, 1.0);	
	aspect_ratio.x = float(ScreenSize.y) / float(ScreenSize.x);

	gl_Position = vec4(position.xy * aspect_ratio + Translate, 0, 1.0);
	TexCoord = texcoord;
	Color = vec4(1.0, 1.0, 1.0, 1.0);
}
