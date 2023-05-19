#ifndef _SHADER_H_
#define _SHADER_H_

typedef struct
{
	unsigned int vs;
	unsigned int fs;
	unsigned int p;
} shader_t;

char *load_file(const char *file_name);
GLuint shader_load(const char *file_name, GLenum type);
shader_t shader_create_program(const char *vertex_file, const char *fragment_file);
void shader_delete(shader_t s);

// Find better way of doing this stuff
void shader_set_uniform2f(shader_t p, const char *name, float v1, float v2);
void shader_set_uniformi(shader_t p, const char *name, int v1);

#endif
