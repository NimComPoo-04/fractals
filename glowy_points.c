#include "shader.h"
#include "glowy_points.h"
#include "state.h"

void create_glowy_points(glowy_points_t *m)
{
	glGenVertexArrays(1, &m->vao);
	glBindVertexArray(m->vao);

	glGenBuffers(1, &m->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof m->position, m->position, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	GLuint vs = create_shader_from_file("shaders/glowy_points_vs.glsl", GL_VERTEX_SHADER);
	GLuint fs = create_shader_from_file("shaders/glowy_points_fs.glsl", GL_FRAGMENT_SHADER);
	GLuint gs = create_shader_from_file("shaders/glowy_points_gs.glsl", GL_GEOMETRY_SHADER);
	m->prog = create_shader_program(3, vs, gs, fs);

	glUseProgram(m->prog);

	m->Type = glGetUniformLocation(m->prog, "Type");
	m->Scale = glGetUniformLocation(m->prog, "Scale");
	m->Center = glGetUniformLocation(m->prog, "Center");
	m->Size = glGetUniformLocation(m->prog, "ScreenSize");
	m->C = glGetUniformLocation(m->prog, "Julia_Set_C");

	glUniform1i(m->Type, gFractals.current);
	glUniform2fv(m->Scale,  1, gFractals.programs[gFractals.current].uniforms[FRACTAL_COMMON_SCALE].f2);
	glUniform2fv(m->Center, 1, gFractals.programs[gFractals.current].uniforms[FRACTAL_COMMON_CENTER].f2);
	glUniform2iv(m->Size,   1, gFractals.programs[gFractals.current].uniforms[FRACTAL_COMMON_SIZE].i2);
	glUniform2fv(m->C,      1, gFractals.programs[gFractals.current].uniforms[FRACTAL_JULIA_SET_C].f2);
}

void update_glowy_points(glowy_points_t *m)
{
	glUseProgram(m->prog);

	glUniform1i(m->Type, gFractals.current);
	glUniform2fv(m->Scale,  1, gFractals.programs[gFractals.current].uniforms[FRACTAL_COMMON_SCALE].f2);
	glUniform2fv(m->Center, 1, gFractals.programs[gFractals.current].uniforms[FRACTAL_COMMON_CENTER].f2);
	glUniform2iv(m->Size,   1, gFractals.programs[gFractals.current].uniforms[FRACTAL_COMMON_SIZE].i2);
	glUniform2fv(m->C,      1, gFractals.programs[gFractals.current].uniforms[FRACTAL_JULIA_SET_C].f2);

	glBindVertexArray(m->vao);
	glBindBuffer(GL_ARRAY_BUFFER, m->vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof m->position, m->position);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void draw_glowy_points(glowy_points_t *k)
{
	glUseProgram(k->prog);
	glBindVertexArray(k->vao);
	glLineWidth(3);
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0);
}

void destroy_glowy_points(glowy_points_t  *k)
{
	glDeleteVertexArrays(1, &k->vao);
	glDeleteBuffers(1, &k->vbo);
}

void update_glowy_points_start(glowy_points_t *g, double x, double y)
{
	double fx = (2 * x / gWidth) - 1;
	double fy = 1 - (2 * y / gHeight);

	glBindVertexArray(g->vao);

	g->position[0] = (float)fx;
	g->position[1] = (float)fy;
}
