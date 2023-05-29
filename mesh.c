#include "mesh.h"

void create_mesh(mesh_t *mesh)
{
	glGenVertexArrays(1, &mesh->vao);
	glGenBuffers(1, &mesh->vbo);
	glGenBuffers(1, &mesh->ibo);

	glBindVertexArray(mesh->vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);

	glBufferData(GL_ARRAY_BUFFER, mesh->number_of_verteces * sizeof(float), mesh->verteces, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->number_of_indeces, mesh->indeces, GL_STATIC_DRAW);

	vertex_attrib_t *b = &mesh->attrib_position;
	glVertexAttribPointer(b->location, b->size, b->type, GL_FALSE, b->stride, (void *)b->position);
	glEnableVertexAttribArray(b->location);

	glBindVertexArray(0);
}

void draw_mesh(mesh_t *mesh)
{
	glBindVertexArray(mesh->vao);
	glDrawElements(mesh->draw_type, mesh->number_of_indeces, GL_UNSIGNED_BYTE, NULL);
}

void draw_mesh_array(mesh_t *mesh)
{
	glBindVertexArray(mesh->vao);
	glDrawArrays(mesh->draw_type, 0, mesh->number_of_verteces);
}

void destroy_mesh(mesh_t *mesh)
{
	glDeleteVertexArrays(1, &mesh->vao);
	glDeleteBuffers(1, &mesh->vbo);
	glDeleteBuffers(1, &mesh->ibo);
}
