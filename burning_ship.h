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
} burning_ship_t;

void create_burning_ship(burning_ship_t *js, GLuint vs, GLuint fs, GLuint texture);

void use_burning_ship_shader(burning_ship_t *ms);
void update_burning_ship_Scale(burning_ship_t *, float a, float b);
void update_burning_ship_Center(burning_ship_t *, float a, float b);
void update_burning_ship_Size(burning_ship_t *, int a, int b);
void update_burning_ship_MaxIteration(burning_ship_t *, int a);

void key_ui_burning_ship_update(burning_ship_t *js, GLFWwindow *win, int key, int action, int mod);

void destroy_burning_ship(burning_ship_t *ms);

#endif
