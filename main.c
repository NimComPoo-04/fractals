#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <assert.h>
#include "fractal_quad.h"


#define WIDTH 800
#define HEIGHT 800

static float scale = 1.0;
static float center_x = 0;
static float center_y = 0;

static void ErrorCallbackGL(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);

void error_callback(int error_code, const char *message)
{
	fprintf(stderr, "[%d]\t%s\n", error_code, message);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	(void)scancode;
	(void)mods;
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	else if(key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		scale *= 1.1;
		fractal_quad_scale(scale, scale);
	}
	else if(key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		scale /= 1.1;
		fractal_quad_scale(scale, scale);
	}
	else if(key == GLFW_KEY_C && action == GLFW_PRESS)
	{
		fractal_quad_bind(MANDELBROT_SET_FRACTAL);
	}
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
	(void)mods;
	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		int width;
		int height;
		glfwGetWindowSize(window, &width, &height);

		double posx;
		double posy;
		glfwGetCursorPos(window, &posx, &posy);

		if(width > height)
		{
			double ratio = 1.0 * width / height;
			posx = (posx / width - 0.5) * ratio / scale;
			posy = (posy / height - 0.5) / scale;
		}
		else
		{
			double ratio = 1.0 * height / width;
			posx = (posx / width - 0.5) / scale;
			posy = (posy / height - 0.5) * ratio / scale;
		}

		center_x += posx;
		center_y -= posy;

		fractal_quad_recenter(center_x, center_y);
	}
}

void size_callback(GLFWwindow* window, int width, int height)
{
	(void) window;
	glViewport(0, 0, width, height);
	fractal_quad_resize(width, height);
}

int main(void)
{
	GLFWwindow *window = NULL;

	assert(glfwInit() != GLFW_FALSE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	window = glfwCreateWindow(WIDTH, HEIGHT, "(o_O)", NULL, NULL);
	assert(window != NULL);

	glfwSetErrorCallback(error_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetWindowSizeCallback(window, size_callback);

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(ErrorCallbackGL, 0);

	glViewport(0, 0, WIDTH, HEIGHT);
	fractal_quad_create(WIDTH, HEIGHT);

	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		fractal_quad_draw();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	fractal_quad_delete();
	glfwDestroyWindow(window);
	glfwTerminate();
}

static void ErrorCallbackGL(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar *message,
		const void *userParam)
{
	(void)id;
	(void)length;
	(void)source;
	(void)userParam;
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
			( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ), type, severity, message);
}
