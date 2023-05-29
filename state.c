#include <glad/glad.h>
#include "state.h"
#include "mesh.h"

int gWidth = 800;
int gHeight = 800;

static float
verteces[12] = {
	-1.0, -1.0, 0.0,
	 1.0, -1.0, 0.0,
	-1.0,  1.0, 0.0,
	 1.0,  1.0, 0.0
};

static unsigned char
indeces[6] = {
	0, 1, 2,
	2, 1, 3
};

mesh_t
gFractalRenderQuad = {
	.vao = 0,
	.vbo = 0,
	.ibo = 0,
	.draw_type = GL_TRIANGLES,
	.attrib_position = {0, 3, GL_FLOAT, 3 * sizeof(float), 0},
	.verteces = verteces,
	.number_of_verteces = sizeof verteces / sizeof(float),
	.indeces = indeces,
	.number_of_indeces = sizeof indeces / sizeof(unsigned char)
};

fractal_t gFractals = {0};

glowy_points_t gGlowyPoints = {0};
