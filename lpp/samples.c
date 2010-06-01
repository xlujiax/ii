#include "samples.h"

Bezier* sample_bezier_sinus(int degree)
{
  Bezier* b = bezier_create(degree);
  for(int i = 0; i <= b->n; ++i)
    b->c[i] = sinf((float)i / (float)b->n * 2.0f);
  return b;
}

Bezier* sample_bezier_cosinus(int degree)
{
  Bezier* b = bezier_create(degree);
  for(int i = 0; i <= b->n; ++i)
    b->c[i] = cosf((float)i / (float)b->n * 2.0f);
  return b;
}

Bezier* sample_bezier_parabola()
{
  Bezier* b = bezier_create(2);
  b->c[0] = 0.3f;
  b->c[1] = -0.4f;
  b->c[2] = 0.4f;
  return b;
}
