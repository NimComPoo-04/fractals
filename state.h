#ifndef _STATE_H_
#define _STATE_H_

#include <stdint.h>

// Screen Width and Height
extern int gWidth;
extern int gHeight;
extern int gFPS;

// Mesh that needs to be rendered

#include "mesh.h"

extern mesh_t gFractalRenderQuad;

// Fractals And Shaders
#include "fractal.h"
extern fractal_t gFractals;

#include "glowy_points.h"
extern glowy_points_t gGlowyPoints;

#include "font.h"
extern font_t gFont;

#endif
