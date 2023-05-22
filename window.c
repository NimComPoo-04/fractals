#include "state.h"
#include "window.h"
#include "fractal.h"
#include <stdio.h>

static void error_handler(int errcode, const char *message)
{
	fprintf(stderr, "[ %d ]\t%s\n", errcode, message);
}

static void size_callback(GLFWwindow *window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
	gWidth = width;
	gHeight = height;

	gFractals[JULIA_SET].uniforms[JULIA_SET_SCREEN_SIZE].value_i2[0] = gWidth;
	gFractals[JULIA_SET].uniforms[JULIA_SET_SCREEN_SIZE].value_i2[1] = gHeight;
	set_uniform(gFractals[JULIA_SET].program, &gFractals[JULIA_SET].uniforms[JULIA_SET_SCREEN_SIZE]);
}

GLFWwindow *create_window()
{
	GLFWwindow *win;

	if(!glfwInit())
		return NULL;

	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	win = glfwCreateWindow(gWidth, gHeight, "(-_-)", NULL, NULL);

	glfwMakeContextCurrent(win);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	glfwSetErrorCallback(error_handler);
	glfwSetWindowSizeCallback(win, size_callback);

	glViewport(0, 0, gWidth, gHeight);

	return win;
}

void start_window_main_loop(GLFWwindow *win, window_update_function_t update)
{
	while(!glfwWindowShouldClose(win))
	{
		if(!update(glfwGetTime()))
			glfwSetWindowShouldClose(win, 1);

		glfwPollEvents();
		glfwSwapBuffers(win);
	}
}

void destroy_window(GLFWwindow *window)
{
	glfwDestroyWindow(window);
	glfwTerminate();
}
