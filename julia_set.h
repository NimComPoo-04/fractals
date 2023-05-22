#ifndef _JULIA_SET_H_
#define _JULIA_SET_H_

#include "glad/glad.h"

typedef struct
{
	GLuint program;
	unifrom_t C;
} julia_set_t;

enum {
	JULIA_SET = 0,
	MANDELBROT_SET,
	TOTAL_FRACTALS
};

typedef struct
{
	julia_set_t julia_set;
	mandelbrot_set_t mandelbrot_set;
} fractal_t;

fractal_t gFractals;
int gCurrentFractal = 0;

#endif
