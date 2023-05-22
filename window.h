#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef int(*window_update_function_t)(double);

GLFWwindow *create_window();
void destroy_window(GLFWwindow *window);
void start_window_main_loop(GLFWwindow *win, window_update_function_t update);

#endif
