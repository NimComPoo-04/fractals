#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <memory.h>
#include "font.h"
#include "shader.h"
#include "state.h"

void load_font_from_file(font_t *f, const char *file)
{
	FILE *k = fopen(file, "rb");
	fseek(k, 0, SEEK_END);
	size_t l = ftell(k);
	fseek(k, 0, SEEK_SET);

	char *data = malloc(l);
	fread(data, l, 1, k);	

	uint32_t fw = *(uint32_t *)(data+2);
	uint32_t fh = *(uint32_t *)(data+6);
	uint32_t cw = *(uint32_t *)(data+10);
	uint32_t ch = *(uint32_t *)(data+14);

	char start = *(data+19);

	glGenTextures(1, &f->texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, f->texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fw, fh, 0, GL_RGBA, GL_UNSIGNED_BYTE, data+276);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	char *cellwidths = data + 20;

	f->chars = calloc(sizeof(float) * 4, 128);

	int rows = fw/cw;
	int cc = fw/cw * fh/ch;
	float wf = 1.0 * cw / fw;
	float hf = 1.0 * ch / fh;

	for(int i = 0; i < cc; i++)
	{
		f->chars[i + start][0] = 1.0 * (i % rows) * wf;
		f->chars[i + start][1] = 1.0 * (i / rows) * hf;
		f->chars[i + start][2] = f->chars[i + start][0] + 1.0 * cellwidths[i + start] / fw;
		f->chars[i + start][3] = f->chars[i + start][1] + hf;
	}

	GLuint vs = create_shader_from_file("shaders/text_vs.glsl", GL_VERTEX_SHADER);
	GLuint fs = create_shader_from_file("shaders/text_fs.glsl", GL_FRAGMENT_SHADER);
	f->prog = create_shader_program(2, vs, fs);
	glDeleteShader(vs);
	glDeleteShader(fs);

	glUseProgram(f->prog);
	f->screen_size_uniform = glGetUniformLocation(f->prog, "ScreenSize");
	font_update_screen_size(f);

	f->translation_uniform = glGetUniformLocation(f->prog, "Translate");
	font_update_translation(f, 0, 0);
	glUseProgram(0);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	free(data);
	fclose(k);
}

void font_update_screen_size(font_t *f)
{
	glUseProgram(f->prog);
	if(f->screen_size_uniform != -1)
		glUniform2i(f->screen_size_uniform, gWidth, gHeight);
	glUseProgram(0);
}

void font_update_translation(font_t *f, float x, float y)
{
	glUseProgram(f->prog);
	if(f->translation_uniform!= -1)
		glUniform2f(f->translation_uniform, x, y);
	glUseProgram(0);
}

static GLuint vao = 0;
static GLuint vbo = 0;

void draw_font(font_t *f)
{
	if(vao == 0)
	{
		float vert[] = {
			-0.5, -0.5, 0,	0.0, 1.0,
			-0.5,  0.5, 0,	0.0, 0.0,
			0.5, -0.5, 0,	1.0, 1.0,
			0.5,  0.5, 0,	1.0, 0.0
		};

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof vert, vert, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void *)(intptr_t)(sizeof(float) * 3));
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	glEnable(GL_BLEND);

	glUseProgram(f->prog);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, f->texture);
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisable(GL_BLEND);
}

void destroy_font(font_t *f)
{
	if(vao)
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}

	free(f->chars);
	glDeleteTextures(1, &f->texture);
	glDeleteProgram(f->prog);
}
