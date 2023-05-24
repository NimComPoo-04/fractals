#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef void(*window_size_change_function_t)(GLFWwindow *win, int width, int height);
typedef void(*window_key_function_t)(GLFWwindow *win, int key, int scancode, int action, int mod);

typedef int(*window_update_function_t)(GLFWwindow *win, double time);

GLFWwindow *create_window(window_size_change_function_t s, window_key_function_t k);

void start_window_main_loop(GLFWwindow *win, window_update_function_t update);

void destroy_window(GLFWwindow *window);

#endif
