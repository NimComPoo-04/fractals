#include <stdio.h>
#include <math.h>

#include "state.h"
#include "window.h"
#include "mesh.h"
#include "shader.h"

static int glowy_should_render = 0;

// FIXME: Counts the Time required to render a scene
static double FPS = 0;

static int update(GLFWwindow *win, double time)
{
	(void)win;
	(void)time;

	glClearColor(1.0, 0.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	if(gFractals.movement_animation.isActive)
	{
		gFractals.movement_animation.update(&gFractals);
	}
	if(gFractals.scaling_animation.isActive)
	{
		gFractals.scaling_animation.update(&gFractals);
	}

	use_fractal(&gFractals);

	draw_mesh(&gFractalRenderQuad);

	if(glowy_should_render)
	{
		update_glowy_points(&gGlowyPoints);
		draw_glowy_points(&gGlowyPoints);
	}

	FPS = (glfwGetTime() - time);

	return 1;
}

void size_change_callback(GLFWwindow *win, int width, int height)
{
	(void)win;

	int *p = gFractals.programs[gFractals.current].uniforms[FRACTAL_COMMON_SIZE].i2;
	p[0] = width;
	p[1] = height;
	set_fractal_uniform(&gFractals, FRACTAL_COMMON_SIZE);
}

void key_callback(GLFWwindow *win, int key, int scancode, int action, int mod)
{
	if(key == GLFW_KEY_SPACE)
	{
		printf("Elapsed Time : %lf\n", FPS);
	}
	else
	{
		fractal_key_control(win, key, scancode, action, mod);
	}
}


void mouse_cursor_callback(GLFWwindow *win, double x, double y)
{
	int state = glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT);
	if(state == GLFW_PRESS)
	{
		update_glowy_points_start(&gGlowyPoints, x, y);
		glowy_should_render = 1;
	}
	else
	{
		glowy_should_render = 0;
	}
}

int main(void)
{
	GLFWwindow *win = create_window(size_change_callback, key_callback);

	glfwSetCursorPosCallback(win, mouse_cursor_callback);

	create_mesh(&gFractalRenderQuad);
	create_fractal(&gFractals);
	create_glowy_points(&gGlowyPoints);

	start_window_main_loop(win, update);

	destroy_glowy_points(&gGlowyPoints);
	destroy_fractal(&gFractals);
	destroy_mesh(&gFractalRenderQuad);
	destroy_window(win);
}
