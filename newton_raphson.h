#ifndef _NEWTON_RAPHSON_H_
#define _NEWTON_RAPHSON_H_

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
} newton_raphson_t;

void create_newton_raphson(newton_raphson_t *js, GLuint vs, GLuint fs, GLuint texture);

void use_newton_raphson_shader(newton_raphson_t *ms);
void update_newton_raphson_Scale(newton_raphson_t *, float a, float b);
void update_newton_raphson_Center(newton_raphson_t *, float a, float b);
void update_newton_raphson_Size(newton_raphson_t *, int a, int b);
void update_newton_raphson_MaxIteration(newton_raphson_t *, int a);

void key_ui_newton_raphson_update(newton_raphson_t *js, GLFWwindow *win, int key, int action, int mod);

void destroy_newton_raphson(newton_raphson_t *ms);

#endif
