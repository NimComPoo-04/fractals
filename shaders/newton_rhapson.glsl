#version 330 core

in vec2 Coordinate;

uniform int MaxIteration;
uniform sampler1D theme_texture;

out vec3 FragColor;

const int root_size = 3;
const vec2 roots[root_size] = {
	vec2(2, 0),
	vec2(-2, 0),
	vec2(0, 2)
};

vec2 cmul(vec2 a, vec2 b)
{
	return vec2(a.x * b.x - a.y * b.y, a.x * b.y + b.x * a.y);
}

vec2 cdiv(vec2 a, vec2 b)
{
	vec2 b2 = vec2(b.x, -b.y);
	return cmul(a, b2) / dot(b2, b2);
}

vec2 F(vec2 x, int skip)
{
	vec2 T = vec2(1, 0);
	for(int i = 0; i < root_size; i++)
	{
		if(skip == i)
			continue;
		T = cmul(T, x - roots[i]);
	}
	return T;
}

vec2 dF(vec2 x)
{
	vec2 T = vec2(0, 0);
	for(int i = 0; i < root_size; i++)
	{
		T += F(x, i);
	}
	return T;
}

void main(void)
{
	vec2 x = vec2(Coordinate);

	for(int i = 0; i < 30; i++)
		x = x - cdiv(F(x, -1), dF(x));

	float l = length(x - roots[0]);
	int mx = 0;

	for(int i = 0; i < root_size; i++)
	{
		float ld = length(x - roots[i]);
		if(ld < l)
		{
			l = ld;
			mx = i;
		}
	}

	FragColor = texelFetch(theme_texture, mx % textureSize(theme_texture, 0), 0).xyz;
}
