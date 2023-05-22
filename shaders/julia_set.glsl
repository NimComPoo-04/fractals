#version 330 core

in vec2 Coordinate;
out vec3 FragColor;

uniform int MaxIteration;
uniform vec2 C;

void main(void)
{
	vec2 Z = vec2(Coordinate);
	int i = 0;

	for(i = 0; i < MaxIteration && dot(Z, Z) < 4.0f; i++)
	{
		Z = vec2(Z.x * Z.x - Z.y * Z.y, 2 * Z.x * Z.y) + C;
	}

	float j = float(i) / MaxIteration;

	FragColor = mix(vec3(0.0, 0.0, 0.0), vec3(1.0, 1.0, 1.0), j);
}
