#ifndef _SHADER_H_
#define _SHADER_H_

#include "glad/glad.h"

GLuint shader_load(const char *file_name, GLenum type);
GLuint shader_link_program(GLuint vs, GLuint fs);
void shader_use(GLuint s);
void shader_uniform(GLuint s, const char *name, GLenum type, ...);
void shader_delete(GLuint s);
#endif
