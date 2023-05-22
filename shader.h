#ifndef _SHADER_H_
#define _SHADER_H_

#include <glad/glad.h>

typedef struct
{
	int updated;		// Keeps a record if a unifrom is updated
	const char *name;
	GLint location;
	GLenum type;
	union
	{
		int   value_i1;
		int   value_i2[2];
		float value_f1;
		float value_f2[2];
	};
} uniform_t;

GLuint create_shader_from_file(const char *filename, GLenum type);
GLuint create_shader_program(int size, ...);
void destroy_shader(GLuint prog);

// FIXME: misleading name, create's no unifrom just fills up the rest of the struct
void create_uniform(GLuint program, uniform_t *uniform);
void set_uniform(GLuint program, uniform_t *uniform);	// sets the updated thing

#endif
