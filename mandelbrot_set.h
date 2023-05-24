#ifndef _BURNING_SHIP_H_
#define _BURNING_SHIP_H_

#include "shader.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

typedef struct
{
	// Shader Program
	GLuint program;
	GLuint theme_texture;	// 1D texture

	// Mathemetical stuff
	uniform_t MaxIteration;

	// Some common stuff ig
	uniform_t Scale;
	uniform_t Center;
	uniform_t ScreenSize;
} mandelbrot_set_t;

void create_mandelbrot_set(mandelbrot_set_t *js, GLuint vs, GLuint fs, GLuint texture);

void use_mandelbrot_set_shader(mandelbrot_set_t *ms);
void update_mandelbrot_set_C(mandelbrot_set_t *, float a, float b);
void update_mandelbrot_set_Scale(mandelbrot_set_t *, float a, float b);
void update_mandelbrot_set_Center(mandelbrot_set_t *, float a, float b);
void update_mandelbrot_set_Size(mandelbrot_set_t *, int a, int b);
void update_mandelbrot_set_MaxIteration(mandelbrot_set_t *, int a);

void key_ui_mandelbrot_set_update(mandelbrot_set_t *js, GLFWwindow *win, int key, int action, int mod);

void destroy_mandelbrot_set(mandelbrot_set_t *ms);

#endif
