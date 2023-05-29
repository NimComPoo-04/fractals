#ifndef _MESH_H_
#define _MESH_H_

#include <glad/glad.h>

typedef struct
{
	unsigned location;
	unsigned size;
	unsigned type;		// GL_FLOAT that stuff
	unsigned stride;
	intptr_t position;
} vertex_attrib_t;

typedef struct
{
	unsigned vao;
	unsigned vbo;
	unsigned ibo;

	vertex_attrib_t attrib_position;

	float *verteces;
	int number_of_verteces;

	unsigned char *indeces;
	int number_of_indeces;

	int draw_type;
} mesh_t;

void create_mesh(mesh_t *mesh);
void draw_mesh(mesh_t *mesh);
void draw_mesh_array(mesh_t *mesh);
void destroy_mesh(mesh_t *mesh);

#endif
