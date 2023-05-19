#ifndef _FRACTAL_QUAD_H_
#define _FRACTAL_QUAD_H_

enum
{
	JULIA_SET_FRACTAL = 0,
	TOTAL_FRACTALS
};

void fractal_quad_create(void);
void fractal_quad_draw(void);
void fractal_quad_delete(void);
void fractal_quad_scale(float scalex, float scaley);
void fractal_quad_resize(int width, int height);
void fractal_quad_recenter(float centerx, float centery);

void fractal_quad_C(float other, float another);
void fractal_quad_maxIteration(int centery);

#endif
