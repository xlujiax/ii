#include "ncs.h"

ncs* ncs_create(control* c)
{
  ncs* n = malloc(sizeof(ncs));
  n->c = c;
  ncs_recalc(n);
  return n;
}

void ncs_recalc(ncs* n)
{
  /*
  n->Mx = realloc(n->Mx, sizeof(float) * n->c->n);
  n->My = realloc(n->My, sizeof(float) * n->c->n);

  // czy na pewno chcemy alokowac n->c->n + 1 czy n->c->n ?
  float* q = (float*)malloc(sizeof(float) * (n->c->n+1));
  float* u = (float*)malloc(sizeof(float) * (n->c->n+1));
  float* p = (float*)malloc(sizeof(float) * (n->c->n+1));
  float* d = (float*)malloc(sizeof(float) * (n->c->n+1));

  // jednoczesne obliczanie Mx i My
  // pomocncze wartosci pk i qk moga byc wspoldzielone, a uk sa zalezne od ilorazow roznicowych

  
  free(q);
  free(u);
  free(p);
  free(d);*/
}

float ncs_eval_x(ncs* n, float t)
{
  // znajdz przedzial w czasie stalym,
  // przez dzielenie - wezly sa rownoodlegle

  // zwroc wynik z wzoru z notatek

  return n->c->pts[0][0] * t + n->c->pts[n->c->n - 1][0] * (1 - t);
}

float ncs_eval_y(ncs* n, float t)
{
  return n->c->pts[0][1] * t + n->c->pts[n->c->n - 1][1] * (1 - t);
}
