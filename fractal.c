#include "state.h"
#include "mesh.h"
#include "fractal.h"

fractal_t create_julia_set_fractal(void)
{
	fractal_t fruc = {0};

	// Selecting type
	fruc.type = JULIA_SET;

	// Creating Shaders
	GLuint vs = create_shader_from_file("shaders/vertex.glsl", GL_VERTEX_SHADER);
	GLuint fs = create_shader_from_file("shaders/julia_set.glsl", GL_FRAGMENT_SHADER);

	fruc.program = create_shader_program(2, vs, fs);

	GLuint s[2];
	int count;
	glGetAttachedShaders(fruc.program, 2, &count, s);

	glDeleteShader(vs);
	glDeleteShader(fs);

	// Attaching Uniforms
	uniform_t Scale = {
		.name = "Scale",
		.type = GL_FLOAT_VEC2,
		.value_f2 = {1.0, 1.0}
	};

	uniform_t Center = {
		.name = "Center",
		.type = GL_FLOAT_VEC2,
		.value_f2 = {0.0, 0.0}
	};

	uniform_t ScreenSize = {
		.name = "ScreenSize",
		.type = GL_INT_VEC2,
		.value_i2 = {gWidth, gHeight}
	};

	uniform_t MaxIteration = {
		.name = "MaxIteration",
		.type = GL_INT,
		.value_i1 = 100
	};

	uniform_t C = {
		.name = "C",
		.type = GL_FLOAT_VEC2,
		.value_f2 = {-0.4, 0.6}
	};

	fruc.uniforms[JULIA_SET_SCALE] = Scale;
	fruc.uniforms[JULIA_SET_CENTER] = Center;
	fruc.uniforms[JULIA_SET_SCREEN_SIZE] = ScreenSize;
	fruc.uniforms[JULIA_SET_MAX_ITERATION] = MaxIteration;
	fruc.uniforms[JULIA_SET_C] = C;
	fruc.number_of_unifroms = 5;

	for(int i = 0; i < fruc.number_of_unifroms; i++)
	{
		create_uniform(fruc.program, fruc.uniforms + i);
	}

	return fruc;
}
