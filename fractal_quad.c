#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"

#define MAX_UNIFORMS (10)

static const float vertex[] = {
	-1.0f, -1.0f, 0.0f,
	-1.0f,  1.0f, 0.0f,
	 1.0f, -1.0f, 0.0f,
	 1.0f,  1.0f, 0.0f
};

static const unsigned char index[] = {
	0, 1, 2,
	2, 1, 3
};

static GLuint VAO = 0;
static GLuint VBO = 0;
static GLuint IBO = 0;

static shader_t prog = {0}; // Shader Program

void fractal_quad_create(void)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof vertex, vertex, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof index, index, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	prog = shader_create_program("shaders/fractal_quad.vs", "shaders/fractal_quad.fs");
}

void fractal_quad_draw(void)
{
	glBindVertexArray(VAO);
	glUseProgram(prog.p);
	glDrawElements(GL_TRIANGLES, sizeof index, GL_UNSIGNED_BYTE, 0);
}

// Scaling the viewport
void fractal_quad_scale(float scalex, float scaley)
{
	glUseProgram(prog.p);
	shader_set_uniform2f(prog, "scale", scalex, scaley);
}

// Scaling the viewport
void fractal_quad_recenter(float centerx, float centery)
{
	glUseProgram(prog.p);
	shader_set_uniform2f(prog, "center", centerx, centery);
}

// Resize the fractal quad if window size change
void fractal_quad_resize(int width, int height)
{
	glUseProgram(prog.p);

	struct
	{
		float a;
		float b;
	} r = {
		.a = 1.0,
		.b = 1.0
	};

	if(width > height)
	{
		r.a = 1.0 * width/height;
		r.b = 1.0;
	}
	else
	{
		r.a = 1.0;
		r.b = 1.0 * height/width;
	}

	shader_set_uniform2f(prog, "ratio", r.a, r.b);
}

void fractal_quad_delete(void)
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &IBO);
	glDeleteBuffers(1, &VBO);
}
