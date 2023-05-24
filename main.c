#include <stdio.h>
#include <math.h>

#include "state.h"
#include "window.h"
#include "mesh.h"
#include "shader.h"

static int update(GLFWwindow *win, double time)
{
	(void)win;
	(void)time;

	glClearColor(1.0, 0.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	switch(gCurrentFractal)
	{
		case JULIA_SET:
			use_julia_set_shader(&gFractalJuliaSet);
			break;

		case MANDELBROT_SET:
			use_mandelbrot_set_shader(&gFractalMandelbrotSet);
			break;

		case BURNING_SHIP:
			use_burning_ship_shader(&gFractalBurningShip);
			break;
	}

	draw_mesh(&gFractalRenderQuad);

	return 1;
}

void size_change_callback(GLFWwindow *win, int width, int height)
{
	(void)win;
	switch(gCurrentFractal)
	{
		case JULIA_SET:
			update_julia_set_Size(&gFractalJuliaSet, width, height);
			break;

		case MANDELBROT_SET:
			update_mandelbrot_set_Size(&gFractalMandelbrotSet, width, height);
			break;

		case BURNING_SHIP:
			update_burning_ship_Size(&gFractalBurningShip, width, height);
			break;
	}
}

void key_callback(GLFWwindow *win, int key, int scancode, int action, int mod)
{
	switch(key)
	{
		case GLFW_KEY_J:
			gCurrentFractal = JULIA_SET;
			break;

		case GLFW_KEY_M:
			gCurrentFractal = MANDELBROT_SET;
			break;

		case GLFW_KEY_B:
			gCurrentFractal = BURNING_SHIP;
			break;
	}

	switch(gCurrentFractal)
	{
		case JULIA_SET:
			key_ui_julia_set_update(&gFractalJuliaSet, win, key, action, mod);
			break;

		case MANDELBROT_SET:
			key_ui_mandelbrot_set_update(&gFractalMandelbrotSet, win, key, action, mod);
			break;

		case BURNING_SHIP:
			key_ui_burning_ship_update(&gFractalBurningShip, win, key, action, mod);
			break;
	}
}

int main(void)
{
	GLFWwindow *win = create_window(size_change_callback, key_callback);
	create_mesh(&gFractalRenderQuad);

	// Shaders
	GLuint vs = create_shader_from_file("shaders/vertex.glsl", GL_VERTEX_SHADER);
	GLuint fs1 = create_shader_from_file("shaders/julia_set.glsl", GL_FRAGMENT_SHADER);
	GLuint fs2 = create_shader_from_file("shaders/mandelbrot_set.glsl", GL_FRAGMENT_SHADER);
	GLuint fs3 = create_shader_from_file("shaders/burning_ship.glsl", GL_FRAGMENT_SHADER);

	// 1D texture themes
	GLuint texture = 0;
	float themes[] = {
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
	};

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_1D, texture);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, sizeof(themes)/sizeof(float)/3, 0, GL_RGB, GL_FLOAT, (void *)themes);
	glGenerateMipmap(GL_TEXTURE_1D);

	create_julia_set(&gFractalJuliaSet, vs, fs1, texture);
	create_mandelbrot_set(&gFractalMandelbrotSet, vs, fs2, texture);
	create_burning_ship(&gFractalBurningShip, vs, fs3, texture);

	glDeleteShader(vs);
	glDeleteShader(fs1);
	glDeleteShader(fs2);
	glDeleteShader(fs3);

	gCurrentFractal = JULIA_SET;

	start_window_main_loop(win, update);

	destroy_julia_set(&gFractalJuliaSet);
	destroy_burning_ship(&gFractalBurningShip);
	destroy_mandelbrot_set(&gFractalMandelbrotSet);

	glDeleteTextures(1, &texture);
	destroy_mesh(&gFractalRenderQuad);
	destroy_window(win);
}
