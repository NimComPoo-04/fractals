#include "buffer_manager.h"

buffer_t buffer_create(const GLfloat *vbo, int lvbo, const GLubyte *ibo, int libo)
{
	buffer_t b = {0};

	glGenVertexArrays(1, &b.vao);
	glGenBuffers(1, &b.vbo);
	glGenBuffers(1, &b.ibo);

	glBindVertexArray(b.vao);
	glBindBuffer(GL_ARRAY_BUFFER, b.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, b.ibo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * lvbo, vbo, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * libo, ibo, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	b.indeces = libo;

	glBindVertexArray(0);
	return b;
}

void buffer_draw(buffer_t b)
{
	glBindVertexArray(b.vao);
	glDrawElements(GL_TRIANGLES, b.indeces, GL_UNSIGNED_BYTE, 0);
}

void buffer_delete(buffer_t b)
{
	glDeleteVertexArrays(1, &b.vao);
	glDeleteBuffers(1, &b.vbo);
	glDeleteBuffers(1, &b.ibo);
}
