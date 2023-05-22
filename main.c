#include <stdio.h>
#include <math.h>

#include "state.h"
#include "window.h"
#include "mesh.h"
#include "shader.h"
#include "fractal.h"

static int update(double time)
{
	(void)time;

	glClearColor(1.0, 0.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	draw_mesh(&gFractalRenderQuad, gFractals[gCurrentFractal].program);

	return 1;
}

int main(void)
{
	win = create_window();
	initialize_program();

	start_window_main_loop(win, update);

	destruct_program();
	destroy_window(win);
}
