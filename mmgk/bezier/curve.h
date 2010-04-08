#pragma once

#include <GL/glut.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

#include "polygon.h"
#include "line.h"

typedef struct
{
  int n; // stopień
  float (*p)[3];
} Curve;

Curve* curve_create(int N);
void curve_destroy(Curve* c);
void curve_draw(Curve* c);
void curve_draw_control_points(Curve* c);
void curve_de_casteljau(Curve* c, float u, float *x, float* y);
void curve_degree_raise(Curve* c, int n);
