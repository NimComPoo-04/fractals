#ifndef _BUFFER_MANAGER_H_
#define _BUFFER_MANAGER_H_

#include <glad/glad.h>

// Very simplistic may need to change later

typedef struct
{
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	int indeces;
} buffer_t;

buffer_t buffer_create(const GLfloat *vbo, int lvbo, const GLubyte *index, int libo);
void buffer_draw(buffer_t b);
void buffer_delete(buffer_t b);

#endif
