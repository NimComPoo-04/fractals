#include "ui.h"

void julia_set_ui(GLFWwindow *win)
{
	int key = glfwGetKey(win, GLFW_KEY_W);
	if(key == GLFW_PRESS || key == GLFW_RELEASE)
	{
		gFractals[JULIA_SET].uniforms[JULIA_SET_SCALE].value_f2[0] *= 1.1;
		gFractals[JULIA_SET].uniforms[JULIA_SET_SCALE].value_f2[1] *= 1.1;
		set_uniform(gFractals[JULIA_SET].program, &gFractals[JULIA_SET].uniforms[JULIA_SET_SCALE]);
	}
}
