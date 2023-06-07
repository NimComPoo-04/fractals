#include <stdio.h>
#include <math.h>

#include "state.h"
#include "window.h"
#include "mesh.h"
#include "shader.h"
#include "font.h"
#include "text.h"

static int glowy_should_render = 0;
static int cam_should_move = 0;

static text_t FPS_text = {0};
static text_t MAXITER_text = {0};
static text_t C_text = {0};
static text_t FRUC_text[MAX_FRACTALS] = {0};

static int frames = 0;

static int update(GLFWwindow *win, double time)
{
	(void)win;
	(void)time;

	if(glowy_should_render)
	{
		double xpos;
		double ypos;
		glfwGetCursorPos(win, &xpos, &ypos);
		update_glowy_points_start(&gGlowyPoints, xpos, ypos);
	}
	if(cam_should_move)
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

	if(frames > 10)
	{
		gFPS = (int)(1.0/(glfwGetTime() - time));

		// draw_font(&gFont);
		char str[4] = {0};
		if(gFPS > 999)
		{
			str[0] = '9';
			str[1] = '9';
			str[2] = '9';
			str[3] = 0;
		}
		else
		{
			str[0] = (gFPS/100)%10 + '0';
			str[1] = (gFPS/10) % 10 + '0';
			str[2] = gFPS % 10 + '0';
			str[3] = 0;
		}
		update_text(&FPS_text, 5, str);
		frames = 0;
	}

	draw_text(&FPS_text);
	draw_text(&FRUC_text[gFractals.current]);
	draw_text(&MAXITER_text);

	if(gFractals.current == JULIA_SET)
	{
		draw_text(&C_text);
	}

	frames++;

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

static void update_MAXITER_text()
{
	int iter = gFractals.programs[gFractals.current].uniforms[FRACTAL_COMMON_MAX_ITERATIONS].i1;
	char str[5] = {0};
	str[0] = iter / 1000 % 10 + '0';
	str[1] = iter / 100 % 10 + '0';
	str[2] = iter / 10 % 10 + '0';
	str[3] = iter % 10 + '0';
	str[4] = 0;
	update_text(&MAXITER_text, 6, str);
}

static void update_C_text()
{
	float *f = gFractals.programs[gFractals.current].uniforms[FRACTAL_JULIA_SET_C].f2;

	char real[10] = {0};
	char imag[10] = {0};

	sprintf(real, "%+1.4f", f[0]);
	sprintf(imag, "%+1.4f", f[1]);

	update_text(&C_text, 3, real);
	update_text(&C_text, 11, imag);
}

void key_callback(GLFWwindow *win, int key, int scancode, int action, int mod)
{
	(void)win;
	(void)scancode;

	if(action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		switch(key)
		{
			case GLFW_KEY_2:
				gFractals.current = JULIA_SET;
				update_MAXITER_text();
				break;

			case GLFW_KEY_1:
				gFractals.current = MANDELBROT_SET;
				update_MAXITER_text();
				break;

			case GLFW_KEY_3:
				gFractals.current = BURNING_SHIP;
				update_MAXITER_text();
				break;

			case GLFW_KEY_4:
				gFractals.current = NEWTON_RAPHSON;
				update_MAXITER_text();
				break;

			case GLFW_KEY_W:
				{
					int iter = ++gFractals.programs[gFractals.current].uniforms[FRACTAL_COMMON_MAX_ITERATIONS].i1;
					if(iter > 1000)
					{
						iter = 1000;
						gFractals.programs[gFractals.current].uniforms[FRACTAL_COMMON_MAX_ITERATIONS].i1 = 1;
					}
					update_MAXITER_text();
					set_fractal_uniform(&gFractals, FRACTAL_COMMON_MAX_ITERATIONS);
				}
				break;

			case GLFW_KEY_S:
				{
					int iter = --gFractals.programs[gFractals.current].uniforms[FRACTAL_COMMON_MAX_ITERATIONS].i1;
					if(iter < 0)
					{
						iter = 0;
						gFractals.programs[gFractals.current].uniforms[FRACTAL_COMMON_MAX_ITERATIONS].i1 = 0;
					}
					update_MAXITER_text();
					set_fractal_uniform(&gFractals, FRACTAL_COMMON_MAX_ITERATIONS);
				}
				break;
	
			case GLFW_KEY_UP:
					    if(gFractals.current == JULIA_SET)
					    {
						    float *f = gFractals.programs[gFractals.current].uniforms[FRACTAL_JULIA_SET_C].f2;

						    if(mod == GLFW_MOD_SHIFT)
							    f[1] += 0.0010;
						    else if(mod == GLFW_MOD_CONTROL)
							    f[1] += 0.0100;
						    else if(mod == GLFW_MOD_ALT)
							    f[1] += 0.1000;
						    else
							    f[1] += 0.0001;


						    if(f[1] > 2.0)
							    f[1] = 2.0;
						    set_fractal_uniform(&gFractals, FRACTAL_JULIA_SET_C);
						    update_C_text();
					    }
					    break;
			case GLFW_KEY_DOWN:
					    if(gFractals.current == JULIA_SET)
					    {
						    float *f = gFractals.programs[gFractals.current].uniforms[FRACTAL_JULIA_SET_C].f2;

						    if(mod == GLFW_MOD_SHIFT)
							    f[1] -= 0.0010;
						    else if(mod == GLFW_MOD_CONTROL)
							    f[1] -= 0.0100;
						    else if(mod == GLFW_MOD_ALT)
							    f[1] -= 0.1000;
						    else
							    f[1] -= 0.0001;


						    if(f[1] < -2.0)
							    f[1] = -2.0;
						    set_fractal_uniform(&gFractals, FRACTAL_JULIA_SET_C);
						    update_C_text();
					    }
					    break;
			case GLFW_KEY_LEFT:
					    if(gFractals.current == JULIA_SET)
					    {
						    float *f = gFractals.programs[gFractals.current].uniforms[FRACTAL_JULIA_SET_C].f2;

						    if(mod == GLFW_MOD_SHIFT)
							    f[0] -= 0.0010;
						    else if(mod == GLFW_MOD_CONTROL)
							    f[0] -= 0.0100;
						    else if(mod == GLFW_MOD_ALT)
							    f[0] -= 0.1000;
						    else
							    f[0] -= 0.0001;


						    if(f[0] < -2.0)
							    f[0] = -2.0;
						    set_fractal_uniform(&gFractals, FRACTAL_JULIA_SET_C);
						    update_C_text();
					    }
					    break;

			case GLFW_KEY_RIGHT:
					    if(gFractals.current == JULIA_SET)
					    {
						    float *f = gFractals.programs[gFractals.current].uniforms[FRACTAL_JULIA_SET_C].f2;

						    if(mod == GLFW_MOD_SHIFT)
							    f[0] += 0.0010;
						    else if(mod == GLFW_MOD_CONTROL)
							    f[0] += 0.0100;
						    else if(mod == GLFW_MOD_ALT)
							    f[0] += 0.1000;
						    else
							    f[0] += 0.0001;

						    if(f[0] > 2.0)
							    f[0] = 2.0;
						    set_fractal_uniform(&gFractals, FRACTAL_JULIA_SET_C);
						    update_C_text();
					    }
					    break;
		}
	}
}

void mouse_button_callback(GLFWwindow *win, int button, int action, int mods)
{
	(void)win;
	(void)mods;

	if(button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if(action == GLFW_PRESS)
		{
			glowy_should_render = 1;
		}
		else
		{
			glowy_should_render = 0;
		}
	}
	else if(button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if(action == GLFW_PRESS)
		{
			cam_should_move = 1;
		}
		else
		{
			cam_should_move = 0;
		}
	}
}

void mouse_scrollback_callback(GLFWwindow *win, double x, double y)
{
	(void)win;
	(void)x;
// XXX: I do not have a single clue why putting 1.8 instead of 1.1 works, its a real mistry but
// 	it does so i am not complaining
// XXX: I always assumed that reapated substration would be division but ig i am wrong
// FIXME: Find out the real mathematical reason behind this weird behavior
	if(y > 0)
	{
		float *f = gFractals.programs[gFractals.current].uniforms[FRACTAL_COMMON_SCALE].f2;

		gFractals.scaling_animation.isActive = gFractals.scaling_animation.time_step;
		gFractals.scaling_animation.dx = 1.1 * f[0] / gFractals.scaling_animation.time_step;
		gFractals.scaling_animation.dy = 1.1 * f[1] / gFractals.scaling_animation.time_step;
	}
	else if(y < 0)
	{
		float *f = gFractals.programs[gFractals.current].uniforms[FRACTAL_COMMON_SCALE].f2;

		gFractals.scaling_animation.isActive = gFractals.scaling_animation.time_step;
		gFractals.scaling_animation.dx = -f[0] / 1.8 / gFractals.scaling_animation.time_step;
		gFractals.scaling_animation.dy = -f[1] / 1.8 / gFractals.scaling_animation.time_step;
	}
}

int main(void)
{
	GLFWwindow *win = create_window(size_change_callback, key_callback);

	glfwSetMouseButtonCallback(win, mouse_button_callback);
	glfwSetScrollCallback(win, mouse_scrollback_callback);

	glClearColor(1.0, 0.0, 1.0, 1.0);

	create_mesh(&gFractalRenderQuad);
	create_fractal(&gFractals);
	create_glowy_points(&gGlowyPoints);

	// START UI
	load_font_from_file(&gFont, "JhengHeiFont.bff");

	FPS_text = create_text(0, 0.2, 0.7, "FPS: 000");
	MAXITER_text = create_text(0, 0.4, 0.7, "ITER: 0100");

	FRUC_text[MANDELBROT_SET] = create_text(0, 0.6, 0.7, "MANDELBROT SET");
	FRUC_text[JULIA_SET] = create_text(0, 0.6, 0.7, "JULIA SET");
	FRUC_text[BURNING_SHIP] = create_text(0, 0.6, 0.7, "BURNING SET");
	FRUC_text[NEWTON_RAPHSON] = create_text(0, 0.6, 0.7, "NEWTON RHAPSON");

	C_text = create_text(0, 0.8, 0.7, "C: -0.4000 +0.6000 I");

	// END UI

	start_window_main_loop(win, update);
	
	destroy_font(&gFont);
	destroy_glowy_points(&gGlowyPoints);
	destroy_fractal(&gFractals);
	destroy_mesh(&gFractalRenderQuad);
	destroy_window(win);
}
