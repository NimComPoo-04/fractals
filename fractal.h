#ifndef _FRACTAL_H_
#define _FRACTAL_H_

#include "shader.h"

#define MAX_UNIFORMS (10)

enum {
	JULIA_SET = 0,
	TOTAL_FRACTALS,
};

typedef struct
{
	int type;
	GLuint program;
	uniform_t uniforms[MAX_UNIFORMS];
	int number_of_unifroms;
} fractal_t;

enum {
	JULIA_SET_SCALE = 0,
	JULIA_SET_CENTER,
	JULIA_SET_SCREEN_SIZE,
	JULIA_SET_MAX_ITERATION,
	JULIA_SET_C,
};

fractal_t create_julia_set_fractal(void);

#endif
