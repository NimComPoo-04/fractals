#include <stdio.h>
#include <stdlib.h>

#include "state.h"
#include "window.h"

typedef struct
{
	window_size_change_function_t size_callback;
	window_key_function_t key_callback;
} callbacks_t;

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

	((callbacks_t *)glfwGetWindowUserPointer(window)) -> size_callback(window, width, height);
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mod)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);

	((callbacks_t *)glfwGetWindowUserPointer(window)) -> key_callback(window, key, scancode, action, mod);
}

GLFWwindow *create_window(window_size_change_function_t s, window_key_function_t k)
{
	GLFWwindow *win;

	if(!glfwInit())
		return NULL;

	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	win = glfwCreateWindow(gWidth, gHeight, "(-_-)", NULL, NULL);

	callbacks_t *callback = calloc(sizeof(callbacks_t), 1);
	callback->size_callback = s;
	callback->key_callback = k;

	glfwSetWindowUserPointer(win, callback);

	glfwMakeContextCurrent(win);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	glfwSetErrorCallback(error_handler);
	glfwSetWindowSizeCallback(win, size_callback);
	glfwSetKeyCallback(win, key_callback);

	glViewport(0, 0, gWidth, gHeight);

	return win;
}

void start_window_main_loop(GLFWwindow *win, window_update_function_t update)
{
	while(!glfwWindowShouldClose(win))
	{
		if(!update(win, glfwGetTime()))
			glfwSetWindowShouldClose(win, 1);

		glfwPollEvents();
		glfwSwapBuffers(win);
	}
}

void destroy_window(GLFWwindow *window)
{
	free(glfwGetWindowUserPointer(window));
	glfwDestroyWindow(window);
	glfwTerminate();
}
