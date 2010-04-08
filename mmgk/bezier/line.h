#pragma once

#include <GL/gl.h>
#include <malloc.h>
#include <math.h>
#include <string.h>

typedef struct
{
  float A, B, C;
} Line;

void line_draw(Line*);
Line* line_create(float a[3], float b[3]);
float line_axis_intersection(Line* l);

typedef struct
{
  float P[3];
  float Q[3];
  Line* ln;
} Segment;

Segment* segment_create(float p[3], float q[3]);
void segment_draw(Segment* s);
int segment_axis_intersection(Segment* s, float* root);
