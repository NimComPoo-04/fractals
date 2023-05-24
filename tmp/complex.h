#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <math.h>

typedef struct
{
	double real;
	double imag;
} complex_t;

static inline complex_t cadd(complex_t a, complex_t b)
{
	return (complex_t){a.real + b.real, a.imag + b.imag};
}

static inline complex_t csub(complex_t a, complex_t b)
{
	return (complex_t){a.real - b.real, a.imag - b.imag};
}

static inline complex_t cmul(complex_t a, complex_t b)
{
	return (complex_t){a.real * b.real - a.imag * b.imag, b.real * a.imag + a.real * b.imag};
}

static inline complex_t cdiv(complex_t a, complex_t b)
{
	complex_t d = {0};
	d.real = a.real * b.real + a.imag * b.imag;
	d.imag = a.imag * b.real - a.real * b.imag;
	double l = b.real * b.real + b.imag * b.imag;
	d.real /= l;
	d.imag /= l;
	return d;
}

static inline double clen(complex_t a)
{
	return sqrt(a.real * a.real + a.imag * a.imag);
}

#endif
