#ifndef _STATE_H_
#define _STATE_H_

#include <stdint.h>

// Screen Width and Height
extern int gWidth;
extern int gHeight;

// Mesh that needs to be rendered

#include "mesh.h"

extern mesh_t gFractalRenderQuad;

// Fractals And Shaders

#include "fractal.h"

extern fractal_t gFractals[TOTAL_FRACTALS];
extern int gCurrentFractal;

void initialize_program(void);
void destruct_program(void);

#endif
