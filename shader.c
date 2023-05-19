#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include "shader.h"

char *load_file(const char *file_name)
{
	FILE *f = fopen(file_name, "r");
	fseek(f, 0, SEEK_END);
	size_t size = ftell(f);
	fseek(f, 0, SEEK_SET);
	char *g = calloc(size, 1);
	fread(g, size, 1, f);
	return g;
}

GLuint shader_load(const char *file_name, GLenum type)
{
	char *src = load_file(file_name);

	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, (const char * const *)&src, NULL);
	glCompileShader(shader);

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

shader_t shader_create_program(const char *vertex_file, const char *fragment_file)
{
	GLuint vs = shader_load(vertex_file, GL_VERTEX_SHADER);
	GLuint fs = shader_load(fragment_file, GL_FRAGMENT_SHADER);
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

	return (shader_t){vs, fs, p};
}

void shader_delete(shader_t s)
{
	glDeleteProgram(s.p);
	glDeleteShader(s.vs);
	glDeleteShader(s.fs);
}

void shader_set_uniform2f(shader_t s, const char *name, float v1, float v2)
{
	GLuint u = glGetUniformLocation(s.p, name);
	glUniform2f(u, v1, v2);
}

void shader_set_uniformi(shader_t s, const char *name, int v1)
{
	GLuint u = glGetUniformLocation(s.p, name);
	glUniform1i(u, v1);
}
