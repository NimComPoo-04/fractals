#version 330 core

in vec2 Coordinate;
out vec3 FragColor;

uniform int MaxIteration;

uniform sampler1D theme_texture;

void main(void)
{
	vec2 C = vec2(Coordinate); 
	vec2 Z = vec2(0.0, 0.0);
	int i = 0;

	for(i = 0; i < MaxIteration && dot(Z, Z) < 4.0f; i++)
	{
		float fx = abs(Z.x);
		float fy = abs(Z.y);

		Z = vec2(fx * fx - fy * fy, 2 * fx * fy) + C;
	}

	int tx = textureSize(theme_texture, 0);
	float j = float(i/tx) / (MaxIteration/tx);

	FragColor = texture(theme_texture, j).xyz;
}
