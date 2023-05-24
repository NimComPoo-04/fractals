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
// TODO: Make this stuff a little bit more extensible??

#include "julia_set.h"
extern julia_set_t gFractalJuliaSet;

#include "mandelbrot_set.h"
extern mandelbrot_set_t gFractalMandelbrotSet;

#include "burning_ship.h"
extern burning_ship_t gFractalBurningShip;

#include "newton_raphson.h"
extern newton_raphson_t gFractalNewtonRaphson;

enum {
	JULIA_SET,
	MANDELBROT_SET,
	BURNING_SHIP,
	NEWTON_RAPHSON
};

extern int gCurrentFractal;

#endif
