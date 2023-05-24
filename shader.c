#include "shader.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

char *load_file(const char *file_name)
{
	char *src = NULL;

	FILE *f = fopen(file_name, "r");

	if(f == NULL)
		return src;

	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);

	src = calloc(size+1, 1);
	src[size] = 0;

	fread(src, 1, size, f);

	fclose(f);

	return src;
}

GLuint create_shader_from_file(const char *filename, GLenum type)
{
	char *c = load_file(filename);

	if(c == NULL)
		return 0;

	GLuint s = glCreateShader(type);
	glShaderSource(s, 1, (const char * const *)&c, 0);

	glCompileShader(s);

	int status = 0;
	glGetShaderiv(s, GL_COMPILE_STATUS, &status);

	if(status != GL_TRUE)
	{
		int length;
		glGetShaderiv(s, GL_INFO_LOG_LENGTH, &length);
		char *message = calloc(length+1, 1);
		glGetShaderInfoLog(s, length, NULL, message);
		fprintf(stderr, "%s\n", message);
		free(message);
	}

	free(c);
	
	return s;
}

GLuint create_shader_program(int size, ...)
{
	GLuint prog = glCreateProgram();

	va_list va;
	va_start(va, size); 

	for(int i = 0; i < size; i++)
	{
		GLuint s = va_arg(va, unsigned);
		glAttachShader(prog, s);
	}

	va_end(va);

	glLinkProgram(prog);

	int status = 0;
	glGetProgramiv(prog, GL_LINK_STATUS, &status);

	if(status != GL_TRUE)
	{
		int length;
		glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &length);
		char *message = calloc(length+1, 1);
		glGetProgramInfoLog(prog, length, NULL, message);
		fprintf(stderr, "%s\n", message);
		free(message);
		return 0;
	}

	glValidateProgram(prog);

	status = 0;
	glGetProgramiv(prog, GL_VALIDATE_STATUS, &status);

	if(status != GL_TRUE)
	{
		int length;
		glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &length);
		char *message = calloc(length+1, 1);
		glGetProgramInfoLog(prog, length, NULL, message);
		fprintf(stderr, "%s\n", message);
		free(message);
		return 0;
	}

	return prog;
}

void destroy_shader(GLuint prog)
{
	glDeleteProgram(prog);
}
