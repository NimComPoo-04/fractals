#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "fractal_quad.h"
#include "shader.h"
#include "buffer_manager.h"

static const float vertex[] = {
	-1.0f, -1.0f, 0.0f,
	-1.0f,  1.0f, 0.0f,
	 1.0f, -1.0f, 0.0f,
	 1.0f,  1.0f, 0.0f
};

static const unsigned char index[] = {
	0, 1, 2,
	2, 1, 3
};

static buffer_t plane = {0};
static GLuint shader_progs[TOTAL_FRACTALS] = {0};
static GLuint prog = 0;

void fractal_quad_create(int width, int height)
{
	plane = buffer_create(vertex, sizeof(vertex) / sizeof(float), index, 6);

	GLuint vs, fs[2];

	vs = shader_load("shaders/fractal_quad.vs", GL_VERTEX_SHADER);

	fs[0] = shader_load("shaders/julia_set_fractal.fs", GL_FRAGMENT_SHADER);
	shader_progs[JULIA_SET_FRACTAL] = shader_link_program(vs, fs[0]);

	fs[1] = shader_load("shaders/mandelbrot_set_fractal.fs", GL_FRAGMENT_SHADER);
	shader_progs[MANDELBROT_SET_FRACTAL] = shader_link_program(vs, fs[1]);

	for(int i = 0; i < TOTAL_FRACTALS; i++)
	{
		prog = shader_progs[i];

		fractal_quad_scale(1, 1);
		fractal_quad_recenter(0, 0);
		fractal_quad_resize(width, height);
	}

	prog = shader_progs[JULIA_SET_FRACTAL];

	shader_use(prog);
}

void fractal_quad_bind(int type)
{
	prog = shader_progs[type];
}

void fractal_quad_draw(void)
{
	shader_use(prog);
	buffer_draw(plane);
}

void fractal_quad_delete(void)
{
	buffer_delete(plane);
	shader_delete(prog);
}

//// MATH LOLZ ////

// Scaling the viewport
void fractal_quad_scale(float scalex, float scaley)
{
	shader_use(prog);
	shader_uniform(prog, "scale", GL_FLOAT_VEC2, scalex, scaley);
}

// Scaling the viewport
void fractal_quad_recenter(float centerx, float centery)
{
	shader_use(prog);
	shader_uniform(prog, "center", GL_FLOAT_VEC2, centerx, centery);
}

// Resize the fractal quad if window size change
void fractal_quad_resize(int width, int height)
{
	shader_use(prog);

	float r[2] = {1.0, 1.0};

	if(width > height)
	{
		r[0] = 1.0 * width/height;
		r[1] = 1.0;
	}
	else
	{
		r[0] = 1.0;
		r[1] = 1.0 * height/width;
	}

	shader_uniform(prog, "ratio", GL_FLOAT_VEC2, r[0], r[1]);
}
