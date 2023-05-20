#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "shader.h"

#define MAX_SHADERS 10

static char *load_file(const char *file_name)
{
	FILE *f = fopen(file_name, "r");
	fseek(f, 0, SEEK_END);
	size_t size = ftell(f);
	fseek(f, 0, SEEK_SET);
	char *g = calloc(size, 1);
	fread(g, size, 1, f);
	return g;
}

// Loads a Shader from file
GLuint shader_load(const char *file_name, GLenum type)
{
	char *src = load_file(file_name);

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, (const char * const *)&src, NULL);
	glCompileShader(shader);

	// Checks errors
	int status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if(!status)
	{
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char *l = calloc(length, 1);
		glGetShaderInfoLog(shader, length, 0, l);
		fprintf(stderr, "%s\n", l);
		free(l);
	}

	free(src);
	return shader;
}

// Links a shader program
GLuint shader_link_program(GLuint vs, GLuint fs)
{
	GLuint p = glCreateProgram();
	glAttachShader(p, vs);
	glAttachShader(p, fs);
	glLinkProgram(p);

	int status;
	glGetProgramiv(p, GL_LINK_STATUS, &status);
	if(!status)
	{
		int length;
		glGetProgramiv(p, GL_INFO_LOG_LENGTH, &length);
		char *l = calloc(length, 1);
		glGetProgramInfoLog(p, length, 0, l);
		fprintf(stderr, "%s\n", l);
		free(l);
	}

	/*
	glDeleteShader(vs);
	glDeleteShader(fs);
	*/

	return p;
}

// Deletes a Shader
void shader_delete(GLuint s)
{
	glDeleteProgram(s);
}

void shader_use(GLuint s)
{
	glUseProgram(s);
}

void shader_uniform(GLuint s, const char *name, GLenum type, ...)
{
	glUseProgram(s);
	GLuint u = glGetUniformLocation(s, name);

	va_list va;
	va_start(va, type);

	switch(type)
	{
		case GL_FLOAT_VEC2:
			{
				double v1 = va_arg(va, double);
				double v2 = va_arg(va, double);
				glUniform2f(u, (float)v1, (float)v2);
			}
			break;

		case GL_INT:
			{
				int v = va_arg(va, int);
				glUniform1i(u, v);
			}
			break;
	}

	va_end(va);
	glUseProgram(0);
}
