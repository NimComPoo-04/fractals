#version 330 core

in vec2 TexCoord;
out vec3 FragColor;

uniform sampler2D tex;

void main(void)
{
	FragColor = texture(tex, TexCoord).xxx;
}
