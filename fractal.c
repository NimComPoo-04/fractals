#include "fractal.h"
#include "state.h"
#include "shader.h"
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

static float themes[] = {
	1.0, 0.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0
};

// total has been calibrated lol
static float newton_rhapson_roots[20] = { -1.0, 0.0, 0.0, 1.0, 1.0, 0.0 };

static void movement_transitions(void *ptr);
static void scaling_transitions(void *ptr);

void create_fractal(fractal_t *f)
{
	f->current = MANDELBROT_SET;
	f->movement_animation.time_step = 20; // Just for testing
	f->movement_animation.update = movement_transitions;

	f->scaling_animation.update = scaling_transitions;
	f->scaling_animation.time_step  = 20; // Just for testing

	GLuint vs  = create_shader_from_file("shaders/vertex.glsl", GL_VERTEX_SHADER);
	GLuint fs1 = create_shader_from_file("shaders/julia_set.glsl", GL_FRAGMENT_SHADER);
	GLuint fs2 = create_shader_from_file("shaders/mandelbrot_set.glsl", GL_FRAGMENT_SHADER);
	GLuint fs3 = create_shader_from_file("shaders/burning_ship.glsl", GL_FRAGMENT_SHADER);
	GLuint fs4 = create_shader_from_file("shaders/newton_raphson.glsl", GL_FRAGMENT_SHADER);

	f->programs[JULIA_SET].program      = create_shader_program(2, vs, fs1);
	f->programs[MANDELBROT_SET].program = create_shader_program(2, vs, fs2);
	f->programs[BURNING_SHIP].program   = create_shader_program(2, vs, fs3);
	f->programs[NEWTON_RAPHSON].program = create_shader_program(2, vs, fs4);

	glGenTextures(1, &f->theme_texture);
	glBindTexture(GL_TEXTURE_1D, f->theme_texture);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, sizeof(themes)/sizeof(float)/3, 0, GL_RGB, GL_FLOAT, (void *)themes);
	glGenerateMipmap(GL_TEXTURE_1D);

	glDeleteShader(vs);
	glDeleteShader(fs1);
	glDeleteShader(fs2);
	glDeleteShader(fs3);
	glDeleteShader(fs4);

	for(int i = 0; i < MAX_FRACTALS; i++)
	{
		glUseProgram(f->programs[i].program);

		f->programs[i].uniforms[FRACTAL_COMMON_SIZE] = (funiform_t) {
			glGetUniformLocation(f->programs[i].program, "ScreenSize"),
				.i2 = {gWidth, gHeight}
		};
		f->current = i;
		set_fractal_uniform(f, FRACTAL_COMMON_SIZE);

		f->programs[i].uniforms[FRACTAL_COMMON_SCALE] = (funiform_t) {
			glGetUniformLocation(f->programs[i].program, "Scale"),
				.f2 = {1.0, 1.0}
		};
		f->current = i;
		set_fractal_uniform(f, FRACTAL_COMMON_SCALE);

		f->programs[i].uniforms[FRACTAL_COMMON_CENTER] = (funiform_t) {
			glGetUniformLocation(f->programs[i].program, "Center"),
				.f2 = {0.0, 0.0}
		};
		f->current = i;
		set_fractal_uniform(f, FRACTAL_COMMON_CENTER);

		f->programs[i].uniforms[FRACTAL_COMMON_MAX_ITERATIONS] = (funiform_t) {
			glGetUniformLocation(f->programs[i].program, "MaxIteration"),
				.i1 = 100
		};
		f->current = i;
		set_fractal_uniform(f, FRACTAL_COMMON_MAX_ITERATIONS);
	}

	f->programs[JULIA_SET].uniforms[FRACTAL_JULIA_SET_C] = (funiform_t) {
		glGetUniformLocation(f->programs[JULIA_SET].program, "C"),
			.f2 = {-0.4, 0.6}
	};
	
	// Julia set specific
	f->current = JULIA_SET;
	set_fractal_uniform(f, FRACTAL_JULIA_SET_C);

	// Newton Raphson specific
	f->current = NEWTON_RAPHSON;

	f->programs[NEWTON_RAPHSON].uniforms[FRACTAL_COMMON_MAX_ITERATIONS].i1 = 10;
	set_fractal_uniform(f, FRACTAL_COMMON_MAX_ITERATIONS);

	f->programs[NEWTON_RAPHSON].uniforms[FRACTAL_NEWTON_RAPHSON_ROOT_SIZE] = (funiform_t) {
		glGetUniformLocation(f->programs[NEWTON_RAPHSON].program, "root_size"),
			.i1 = 3
	};
	set_fractal_uniform(f, FRACTAL_NEWTON_RAPHSON_ROOT_SIZE);

	f->programs[NEWTON_RAPHSON].uniforms[FRACTAL_NEWTON_RAPHSON_ROOTS] = (funiform_t) {
		glGetUniformLocation(f->programs[NEWTON_RAPHSON].program, "roots"),
			.fptr = newton_rhapson_roots,
			.count = 3
	};
	set_fractal_uniform(f, FRACTAL_NEWTON_RAPHSON_ROOTS);

	f->current = MANDELBROT_SET;
}

void set_fractal_uniform(fractal_t *f, int pos)
{
	program_t *p = &f->programs[f->current];

	glUseProgram(p->program);

	switch(pos)
	{
		// 2 ints
		case FRACTAL_COMMON_SIZE:
			glUniform2iv(p->uniforms[pos].location, 1, p->uniforms[pos].i2);
			break;

			// 1 int
		case FRACTAL_COMMON_MAX_ITERATIONS:
			glUniform1i(p->uniforms[pos].location, p->uniforms[pos].i1);
			break;

			// 2 floats
		case FRACTAL_COMMON_SCALE:
		case FRACTAL_COMMON_CENTER:
			glUniform2fv(p->uniforms[pos].location, 1, p->uniforms[pos].f2);
			break;

		case FRACTAL_JULIA_SET_C:
			if(f->current != JULIA_SET) return;
			glUniform2fv(p->uniforms[pos].location, 1, p->uniforms[pos].f2);
			break;

		case FRACTAL_NEWTON_RAPHSON_ROOT_SIZE:
			if(f->current != NEWTON_RAPHSON) return;
			glUniform1i(p->uniforms[pos].location, p->uniforms[pos].i1);
			break;

		case FRACTAL_NEWTON_RAPHSON_ROOTS:
			if(f->current != NEWTON_RAPHSON) return;
			glUniform2fv(p->uniforms[pos].location, p->uniforms[pos].count, p->uniforms[pos].fptr);
			break;

		default:
			printf("WRONG ACESS :: %d\n", pos);
	}
}

void use_fractal(fractal_t *f)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_1D, f->theme_texture);
	glUseProgram(f->programs[f->current].program);

	int *i = f->programs[f->current].uniforms[FRACTAL_COMMON_SIZE].i2;
	i[0] = gWidth;
	i[1] = gHeight;
	set_fractal_uniform(f, FRACTAL_COMMON_SIZE);
}

void destroy_fractal(fractal_t *f)
{
	for(int i = 0; i < MAX_FRACTALS; i++)
	{
		glDeleteProgram(f->programs[i].program);
	}
	glDeleteTextures(1, &f->theme_texture);
}

void fractal_key_control(GLFWwindow *win, int key, int scancode, int action, int mod)
{
	(void)scancode;
	(void)mod;

	if(action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		switch(key)
		{
			case GLFW_KEY_J:
				gFractals.current = JULIA_SET;
				break;

			case GLFW_KEY_M:
				gFractals.current = MANDELBROT_SET;
				break;

			case GLFW_KEY_B:
				gFractals.current = BURNING_SHIP;
				break;

			case GLFW_KEY_N:
				gFractals.current = NEWTON_RAPHSON;
				break;

			case GLFW_KEY_W:
				{
					float *f = gFractals.programs[gFractals.current].uniforms[FRACTAL_COMMON_SCALE].f2;

					gFractals.scaling_animation.isActive = gFractals.scaling_animation.time_step;
					gFractals.scaling_animation.dx = 1.1 * f[0] / gFractals.scaling_animation.time_step;
					gFractals.scaling_animation.dy = 1.1 * f[1] / gFractals.scaling_animation.time_step;
				}
				break;

// XXX: I do not have a single clue why putting 1.8 instead of 1.1 works, its a real mistry but
// 	it does so i am not complaining
// XXX: I always assumed that reapated substration would be division but ig i am wrong
// FIXME: Find out the real mathematical reason behind this weird behavior
			case GLFW_KEY_S:
				{
					float *f = gFractals.programs[gFractals.current].uniforms[FRACTAL_COMMON_SCALE].f2;

					gFractals.scaling_animation.isActive = gFractals.scaling_animation.time_step;
					gFractals.scaling_animation.dx = -f[0] / 1.8 / gFractals.scaling_animation.time_step;
					gFractals.scaling_animation.dy = -f[1] / 1.8 / gFractals.scaling_animation.time_step;
				}
				break;

			case GLFW_KEY_V:
				{
					double xpos;
					double ypos;
					glfwGetCursorPos(win, &xpos, &ypos);

					double gx = (2.0 * xpos / gWidth) - 1;
					double gy = (2.0 * ypos / gHeight) - 1;

					float ratio[2] = {1.0, 1.0};

					if(gWidth > gHeight)
					{
						ratio[0] = 1.0 * gWidth / gHeight;
						ratio[1] = 1.0;
					}
					else
					{
						ratio[0] = 1.0;
						ratio[1] = 1.0 * gHeight / gWidth;
					}

					float *Scale = gFractals.programs[gFractals.current].uniforms[FRACTAL_COMMON_SCALE].f2;

					float x = ratio[0] * (float)gx / Scale[0];
					float y = -ratio[1] * (float)gy / Scale[1];

					gFractals.movement_animation.isActive = gFractals.movement_animation.time_step;
					gFractals.movement_animation.dx = x / gFractals.movement_animation.time_step;
					gFractals.movement_animation.dy = y / gFractals.movement_animation.time_step;
				}
				break;
		}
	}
}

static void movement_transitions(void *ptr)
{
	fractal_t *f = (fractal_t *)ptr;
	float *Center = f->programs[f->current].uniforms[FRACTAL_COMMON_CENTER].f2;

	Center[0] += f->movement_animation.dx;
	Center[1] += f->movement_animation.dy;

	set_fractal_uniform(f, FRACTAL_COMMON_CENTER);
	f->movement_animation.isActive--;
}

static void scaling_transitions(void *ptr)
{
	fractal_t *g = ptr;

	float *f = g->programs[g->current].uniforms[FRACTAL_COMMON_SCALE].f2;
	f[0] += g->scaling_animation.dx;
	f[1] += g->scaling_animation.dy;

	set_fractal_uniform(g, FRACTAL_COMMON_SCALE);
	g->scaling_animation.isActive--;
}
