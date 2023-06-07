#ifndef _TEXT_H_
#define _TEXT_H_

#include <glad/glad.h>

typedef struct
{
	GLuint vao;
	GLuint vbo;
	float x; float y;
	float s;
	float *verteces;
	int length;
} text_t;

text_t create_text(float x, float y, float s, const char *str);
void update_text(text_t *t, int loc, const char *c);
void draw_text(text_t *text);

#endif
