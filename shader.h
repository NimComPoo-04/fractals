#ifndef _SHADER_H_
#define _SHADER_H_

#include <glad/glad.h>

GLuint create_shader_from_file(const char *filename, GLenum type);
GLuint create_shader_program(int size, ...);
void destroy_shader(GLuint prog);

#endif
