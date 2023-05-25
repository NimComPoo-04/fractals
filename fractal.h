#ifndef _FRACTAL_H_
#define _FRACTAL_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

enum {
	JULIA_SET = 0,
	MANDELBROT_SET,
	BURNING_SHIP,
	NEWTON_RAPHSON,
	MAX_FRACTALS
};

enum {
	FRACTAL_COMMON_SIZE = 0,
	FRACTAL_COMMON_SCALE,
	FRACTAL_COMMON_CENTER,
	FRACTAL_COMMON_MAX_ITERATIONS,

	FRACTAL_JULIA_SET_C,

	FRACTAL_NEWTON_RAPHSON_ROOT_SIZE,
	FRACTAL_NEWTON_RAPHSON_ROOTS,

	MAX_UNIFORMS
};

typedef struct
{
	GLint location;
	union
	{
		float f1;
		int i1;
		float f2[2];
		int i2[2];
		float *fptr;
		int *iptr;
	};
	int count;
} funiform_t;

typedef struct
{
	GLuint program;
	funiform_t uniforms[MAX_UNIFORMS];
} program_t;

typedef struct
{
	int isActive;
	float dx; float dy;
	void(*update)(void *);	// accepts fractal_t
	int time_step;
} transition_t;

typedef struct
{
	int current;
	program_t programs[MAX_FRACTALS];
	GLuint theme_texture;

	transition_t movement_animation;
	transition_t scaling_animation;
} fractal_t;

void create_fractal(fractal_t *f);
void set_fractal_uniform(fractal_t *f, int pos);
void use_fractal(fractal_t *f);
void destroy_fractal(fractal_t *f);

void fractal_key_control(GLFWwindow *win, int key, int scancode, int action, int mod);

#endif
