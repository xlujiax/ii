#include "curve.h"

Curve* curve_create(int N)
{
  Curve* c = malloc(sizeof(Curve));
  c->n = N;
  c->p = (float(*)[3])malloc(sizeof(float) * (c->n + 1) * 3);

  return c;
}

void curve_draw(Curve* c)
{
  glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, c->n+1, &c->p[0][0]);

  // todo: liczba segmentów powinna zależeć od długości krzywej
  const int segments = 50;
  glMapGrid1f(segments, 0, 1);
  glEvalMesh1(GL_LINE, 0, segments);
}

void curve_draw_control_points(Curve* c)
{
  glPointSize(5.0);
  glBegin(GL_POINTS);
  for (int i = 0; i <= c->n; i++)
    glVertex3fv(&c->p[i][0]);
  glEnd();
}

void curve_destroy(Curve* c)
{
  free(c->p);
  free(c);
  c = 0;
}

void curve_de_casteljau(Curve* c, float u, float *x, float* y)
{
  float (*b)[c->n + 1] = calloc((c->n + 1) * (c->n + 1), sizeof(float));

  {
    for(int i = 0; i <= c->n; ++i)
      b[0][i] = c->p[i][0];
    
    for(int j = 1; j <= c->n; ++j)
      for(int i = 0; i <= c->n - j; ++i)
	b[j][i] = (1.0f - u) * b[j-1][i] + u * b[j-1][i+1];

    *x = b[c->n][0];
  }

  {
    for(int i = 0; i <= c->n; ++i)
      b[0][i] = c->p[i][1];
    
    for(int j = 1; j <= c->n; ++j)
      for(int i = 0; i <= c->n - j; ++i)
	b[j][i] = (1.0f - u) * b[j-1][i] + u * b[j-1][i+1];

    *y = b[c->n][0];
  }

  free(b);
}

void curve_degree_raise(Curve* c, int M)
{
  // zapamiętujemy zakres wielomianu
  float min_x = c->p[0][0];
  float max_x = c->p[c->n][0];

  c->p = realloc(c->p, sizeof(float) * 3 * (M + 1));
  
  for(int m = c->n + 1; m <= M; ++m, ++c->n)
  {
    c->p[m][1] = c->p[c->n][1];
    for(int i = c->n; i >= 1; --i)
      c->p[i][1] = (i*c->p[i-1][1]+(m-i)*c->p[i][1])/((float)m);
  }

  for(int i = 0; i <= c->n; ++i)
  {
    c->p[i][0] = min_x + (max_x - min_x)*((float)i) / ((float)c->n);
    c->p[i][2] = 0;
  }
}

float curve_max_diff(Curve* c1, Curve* c2)
{
  assert(c1->n == c2->n);

  float diff = 0;
  for(int i = 0; i <= c1->n; ++i)
    diff = max(diff, c1->p[i][1] - c2->p[i][1]);

  return diff;
}
