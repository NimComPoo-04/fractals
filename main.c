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

	if(gFractals.movement_animation.isActive)
	{
		float *Center = gFractals.programs[gFractals.current].uniforms[FRACTAL_COMMON_CENTER].f2;

		Center[0] += gFractals.movement_animation.dx;
		Center[1] += gFractals.movement_animation.dy;

		set_fractal_uniform(&gFractals, FRACTAL_COMMON_CENTER);
		gFractals.movement_animation.isActive--;
	}

	use_fractal(&gFractals);

	draw_mesh(&gFractalRenderQuad);

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
	fractal_key_control(win, key, scancode, action, mod);
}

int main(void)
{
	GLFWwindow *win = create_window(size_change_callback, key_callback);

	create_mesh(&gFractalRenderQuad);
	create_fractal(&gFractals);

	start_window_main_loop(win, update);

	destroy_fractal(&gFractals);
	destroy_mesh(&gFractalRenderQuad);
	destroy_window(win);
}
