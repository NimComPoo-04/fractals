#ifndef _GLOWY_POINTS_H_
#define _GLOWY_POINTS_H_

#include <glad/glad.h>
#include "fractal.h"

typedef struct
{
	GLuint vao;
	GLuint vbo;
	GLuint prog;
	float position[3];

	GLint Type;
	GLint Scale;
	GLint Center;
	GLint Size;
	GLint C;

} glowy_points_t;

void create_glowy_points(glowy_points_t *m);
void update_glowy_points(glowy_points_t *k);
void update_glowy_points_start(glowy_points_t *g, double x, double y);
void draw_glowy_points(glowy_points_t *k);
void destroy_glowy_points(glowy_points_t  *k);

#endif
