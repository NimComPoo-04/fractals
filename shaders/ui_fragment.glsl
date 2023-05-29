#version 330 core

in vec2 TexCoord;
in vec3 Color;

out vec3 FragColor;

uniform sampler2D Texture;

void main(void)
{
	FragColor = texture(Texture, TexCoord) * Color;
}
