#version 330 core

in vec2 TexCoord;
in vec4 Color;

uniform sampler2D Tex;

out vec4 FragColor;

void main(void)
{
	FragColor = texture(Tex, TexCoord) * Color;
}
