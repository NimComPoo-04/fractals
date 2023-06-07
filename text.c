#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "text.h"
#include "shader.h"
#include "state.h"

#define VERT 5

text_t create_text(float x, float y, float w, const char *str)
{
	text_t t = {0}; 
	t.x = x/2 - 1.0;
	t.y = 1.0 - y/2;
	t.s = w;

	size_t s = 0;
	t.length = strlen(str);

	t.verteces = malloc(t.length * sizeof(float) * VERT * 4);

	float fx = 0;

	for(int i = 0; i < t.length; i++)
	{
		float *ftx = gFont.chars[(int)str[i]];

		float sy = t.s * (ftx[3] - ftx[1]);
		float sx = t.s * (ftx[2] - ftx[0]);

		float vert[] =
		{
			fx,  	 0,   0,	ftx[0], ftx[3],
			fx,  	 sy,  0,        ftx[0], ftx[1],
			fx + sx,  0,  0,	ftx[2], ftx[3],
			fx + sx, sy,  0,	ftx[2], ftx[1]
		};

		memcpy((char *)t.verteces + s, vert, sizeof vert);
		s += sizeof vert;
		fx += sx;
	}	

	glGenVertexArrays(1, &t.vao);
	glBindVertexArray(t.vao);

	glGenBuffers(1, &t.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, t.vbo);
	glBufferData(GL_ARRAY_BUFFER, s, t.verteces, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * VERT, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * VERT, sizeof(float) * 3);
/*
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * VERT, sizeof(float) * 5);
	*/

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return t;
}

void update_text(text_t *t, int loc, const char *c)
{
	glBindBuffer(GL_ARRAY_BUFFER, t->vbo);
	int l = strlen(c);

	for(int i = 0; i < l; i++)
	{
		float *v = t->verteces + loc * VERT * 4;
		float *f = gFont.chars[(int)c[i]];

		v[3] = f[0]; v[4] = f[3];
		v += VERT;
		v[3] = f[0]; v[4] = f[1];
		v += VERT;
		v[3] = f[2]; v[4] = f[3];
		v += VERT;
		v[3] = f[2]; v[4] = f[1];

		v = t->verteces + loc * VERT * 4;
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * loc * VERT * 4, sizeof(float) * VERT * 4, v);
		loc++;
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// FIXME: use instancing instead of whatever this bs is
void draw_text(text_t *text)
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_BLEND);

	font_update_screen_size(&gFont);
	font_update_translation(&gFont, text->x, text->y);

	glUseProgram(gFont.prog);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gFont.texture);

	glBindVertexArray(text->vao);
	for(int i = 0; i < text->length; i++)
	{
		glDrawArrays(GL_TRIANGLE_STRIP, i * 4, 4);
	}
	// glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, text->length);

	glDisable(GL_BLEND);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
