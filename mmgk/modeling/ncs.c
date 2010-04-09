#include "ncs.h"

ncs* ncs_create(control* c)
{
  ncs* n = malloc(sizeof(ncs));
  n->c = c;
  n->Mx = 0;
  n->My = 0;
  ncs_recalc(n);
  return n;
}

void ncs_recalc(ncs* n)
{
  n->Mx = realloc(n->Mx, sizeof(float) * n->c->n);
  n->My = realloc(n->My, sizeof(float) * n->c->n);

  float* q = malloc(sizeof(float) * (n->c->n+1));
  float* p = malloc(sizeof(float) * (n->c->n+1));
  float* ux = malloc(sizeof(float) * (n->c->n+1));
  float* uy = malloc(sizeof(float) * (n->c->n+1));
  float* dx = malloc(sizeof(float) * (n->c->n+1));
  float* dy = malloc(sizeof(float) * (n->c->n+1));

  // jednoczesne obliczanie Mx i My
  // pomocncze wartosci pk i qk moga byc wspoldzielone, a uk sa zalezne od ilorazow roznicowych

  const float h = 1.0 / (float)n->c->n;
  const float lambda = 0.5;

  // iloczyny roznicowe
  for(int k = 1; k <= n->c->n-1; ++k)
  {
    dx[k] = 6 * (n->c->pts[k-1][0] + n->c->pts[k][0] + n->c->pts[k+1][0]) / (h * h);
    dx[k] = 6 * (n->c->pts[k-1][1] + n->c->pts[k][1] + n->c->pts[k+1][1]) / (h * h);
  }

  q[0] = 0;
  ux[0] = uy[0] = 0;
  for(int k = 1; k <= n->c->n - 1; ++k)
  {
    // wartości p i q są współdzielone przy obliczaniu ux i uy
    p[k] = lambda*q[k-1]+2;
    q[k] = (lambda - 1)/p[k];

    // osobne obliczenia dla obu współrzędnych
    ux[k] = (dx[k] - lambda*ux[k-1])/p[k];
    uy[k] = (dy[k] - lambda*uy[k-1])/p[k];
  }

  // rozwiązanie układu dla momentów

  n->Mx[n->c->n-1] = ux[n->c->n-1];
  n->My[n->c->n-1] = uy[n->c->n-1];
  for(int k = n->c->n - 2; k >= 0; --k)
  {
    n->Mx[k] = ux[k] + q[k]*n->Mx[k+1];
    n->My[k] = uy[k] + q[k]*n->My[k+1];
  }
  
  free(q);
  free(p);
  free(ux);
  free(uy);
  free(dx);
  free(dy);
}

float ncs_eval_x(ncs* n, float t)
{
  const int k = (int)(t*n->c->n) + 1; // przedzial
  const float h = 1.0 / (float)n->c->n;

  const float xk = (float)k / (float)n->c->n;
  const float xkm1 = (float)(k-1) / (float)n->c->n;
  
  return (n->Mx[k-1]*(xk - t)*(xk - t)*(xk - t)/6 +
    n->Mx[k]*(t - xkm1)*(t - xkm1)*(t - xkm1)/6 +
    (n->c->pts[k-1][0] - n->Mx[k-1]*h*h/6)*(xk - t) +
    (n->c->pts[k][0] - n->Mx[k]*h*h/6)*(t - xkm1))/h;
}

float ncs_eval_y(ncs* n, float t)
{
  const int k = (int)(t*n->c->n) + 1; // przedzial
  const float h = 1.0 / (float)n->c->n;

  const float xk = (float)k / (float)n->c->n;
  const float xkm1 = (float)(k-1) / (float)n->c->n;
  
  return (n->My[k-1]*(xk - t)*(xk - t)*(xk - t)/6 +
    n->My[k]*(t - xkm1)*(t - xkm1)*(t - xkm1)/6 +
    (n->c->pts[k-1][1] - n->My[k-1]*h*h/6)*(xk - t) +
    (n->c->pts[k][1] - n->My[k]*h*h/6)*(t - xkm1))/h;
}
