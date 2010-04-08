#pragma once

#include <GL/glut.h>
#include <math.h>
#include <malloc.h>
#include <string.h>

#include "utils.h"
#include "line.h"

typedef struct
{
  int n;
  float (*p)[3];
} Polygon;

Polygon* polygon_create(int n);
void polygon_destroy(Polygon* poly);
void polygon_draw(Polygon* poly);
void polygon_draw_wire(Polygon* poly);
int polygon_axis_intersection(Polygon* poly, float **ret_ints);
