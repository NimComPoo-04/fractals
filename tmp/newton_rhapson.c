#include <stdint.h>
#include <memory.h>
#include <stdio.h>
#include <math.h>
#include "complex.h"

#define WIDTH  256
#define HEIGHT 256
#define N 10

#pragma pack(push, 1)

struct {
	char c[3];
} buffer[WIDTH * HEIGHT] = {0};

#pragma pack(pop)

void ppx(int x, int y, char col[3])
{
	memcpy(&buffer[y * WIDTH + x], col, 3);
}

complex_t F(complex_t coord, int i);
complex_t dF(complex_t Z);

double scale = 3;

#define RS (sizeof(root)/sizeof(complex_t))
complex_t root[] = {{-2, 0}, {2, 0}, {0,-2}};
char color[RS][3] = {{255, 0, 0}, {0, 255, 0}, {0, 0, 255}};

int main(void)
{
	FILE *f = fopen("nprs.ppm", "wb+");
	fprintf(f, "P6\n%d %d %d\n", WIDTH, HEIGHT, 255);

	for(int i = 0; i < WIDTH; i++)
	{
		for(int j = 0; j < HEIGHT; j++)
		{
			char col[3] = {0, 0, 0};

			complex_t x = {
				2.0 * i * scale / WIDTH - scale,
				2.0 * j * scale / HEIGHT - scale
			};

			for(int i = 0; i < N; i++)
				x = csub(x, cdiv(F(x, -1), dF(x)));

			double l = clen(csub(root[0], x));
			int mx = 0;
			for(int i = 1; i < RS; i++)
			{
				double ld = clen(csub(root[i], x));
				if(ld < l)
				{
					l = ld;
					mx = i;
				}
			}

			ppx(i, j, color[mx]);
		}
	}

	fwrite(buffer, sizeof buffer, 1, f);
	fclose(f);
}

complex_t F(complex_t coord, int s)
{
	complex_t T = {1, 0};

	for(int i = 0; i < RS; i++)
	{
		if(i == s) continue;
		T = cmul(T, csub(coord, root[i]));
	}

	return T;
}

complex_t dF(complex_t Z)
{
	complex_t T = {0, 0};

	for(int i = 0; i < RS; i++)
	{
		T = cadd(T, F(T, i));
	}

	return T;
}
