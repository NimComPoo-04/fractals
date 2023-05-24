#ifndef _JULIA_SET_H_
#define _JULIA_SET_H_

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "shader.h"

typedef struct
{
	// Shader Program
	GLuint program;
	GLuint theme_texture;	// 1D texture

	// Mathemetical stuff
	uniform_t C;
	uniform_t MaxIteration;

	// Some common stuff ig
	uniform_t Scale;
	uniform_t Center;
	uniform_t ScreenSize;
} julia_set_t;

void create_julia_set(julia_set_t *js, GLuint vs, GLuint fs, GLuint texture);

void use_julia_set_shader(julia_set_t *js);
void update_julia_set_C(julia_set_t *, float a, float b);
void update_julia_set_Scale(julia_set_t *, float a, float b);
void update_julia_set_Center(julia_set_t *, float a, float b);
void update_julia_set_Size(julia_set_t *, int a, int b);
void update_julia_set_MaxIteration(julia_set_t *, int a);

void key_ui_julia_set_update(julia_set_t *js, GLFWwindow *win, int key, int action, int mod);

void destroy_julia_set(julia_set_t *js);

#endif
