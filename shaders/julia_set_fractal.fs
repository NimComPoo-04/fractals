#version 330 core

precision highp float ;

in vec2 coordinates;
out vec3 Fragcolor;

const vec3 thematic_colors[10] = {
	vec3(0.0, 0.0, 0.0),
	vec3(0.0, 0.0, 0.3),
	vec3(0.0, 0.3, 0.5),
	vec3(0.3, 0.4, 0.6),
	vec3(0.4, 0.6, 0.4),
	vec3(0.5, 0.8, 0.2),
	vec3(0.7, 0.5, 0.0),
	vec3(0.8, 0.3, 0.1),
	vec3(0.8, 0.2, 0.6),
	vec3(0.7, 0.6, 0.5)
};

void main(void)
{
	vec2 C = vec2(-0.4, 0.6);
	int max_iter = 100;
	vec2 Z = vec2(coordinates.xy);
	int i = 0;

	for(i = 0; i <= max_iter && dot(Z, Z) < 4; i++)
	{
		Z = vec2(Z.x * Z.x - Z.y * Z.y, 2 * Z.x * Z.y) + C;
	}

	float j = float(i);

	Fragcolor = thematic_colors[i % 10];
}
