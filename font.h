#ifndef _FONT_H_
#define _FONT_H_

#include <glad/glad.h>

#define MAX_CHARS 128

typedef struct
{
	GLuint texture;
	GLuint prog;
	GLint screen_size_uniform;
	GLint translation_uniform;
	float (*chars)[4]; // uv coord of the chars
} font_t;

void load_font_from_file(font_t *f, const char *file);
void font_update_screen_size(font_t *f);
void font_update_translation(font_t *f, float x, float y);
void draw_font(font_t *f);
void destroy_font(font_t *f);

#endif
