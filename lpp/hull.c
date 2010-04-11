#include "hull.h"

// prywatne funkcje i zmienne funkcji curve_convex_hull:

float *first_pt;

// funkcja alpha z http://www.algorytm.org/index.php?option=com_content&task=view&id=71&Itemid=5
float alpha(float x, float y)
{
  /*float d = fabs(x) + fabs(y);
  if(x >= 0)
  {
    if(y >= 0)
      return y / d;
    else
      return 4 - fabs(y) / d;
  }
  else
  {
    if(y > 0)
      return 2 - y / d;
    else
      return 2 + fabs(y) / d;
      }
      return 0;*/
  return atan2(y,x);
}

// ang. counter clock wise
// zwraca liczbę większą od zera, jeśli c jest na lewo od prostej ab
float ccw(float* a, float* b, float* c)
{
  return (b[0] - a[0])*(c[1] - a[1]) - (b[1] - a[1])*(c[0] - a[0]);
}

int angle_comparator(const void* a, const void* b)
{
  float *fa = (float*)a;
  float *fb = (float*)b;

  // absolutne wspolrzedne wg first_pt
  float xa = fa[0] - first_pt[0];
  float ya = fa[1] - first_pt[1];
  float xb = fb[0] - first_pt[0];
  float yb = fb[1] - first_pt[1];

  if(alpha(xb, yb) < alpha(xa, ya))
    return 1;
  if(alpha(xb, yb) > alpha(xa, ya))
    return -1;
  return 0;
}

// algorytm Grahama
Polygon* curve_convex_hull(Curve* c)
{
  float (*pts)[3];
  pts = malloc(sizeof(float) * 3 * (c->n+2));
  memcpy(pts[1], c->p, sizeof(float) * (c->n+1) * 3);

  int lowest_y = 1;
  for(int i = 2; i <= c->n + 1; ++i)
    if(pts[i][1] < pts[lowest_y][1] || (pts[i][1] == pts[lowest_y][1] && pts[i][0] < pts[lowest_y][0]))
      lowest_y = i;

  {
    float (*temp)[3] = malloc(sizeof(float) * 3);
    memcpy(temp, pts[1], sizeof(float) * 3);

    memcpy(pts[1], pts[lowest_y], sizeof(float) * 3);
    memcpy(pts[lowest_y], temp, sizeof(float) * 3);
  }

  first_pt = malloc(sizeof(float) * 3);
  memcpy(first_pt, pts[1], sizeof(float) * 3);

  // sortujemy od trzeciego elementu, jest ich c->n
  qsort(pts[2], c->n, sizeof(float) * 3, angle_comparator);
  
  // straznik
  memcpy(pts[0], pts[c->n+1], sizeof(float) * 3);

  
  // umieszczenie 3 pierwszych wierzcholków na stosie
  int top = 2;
  
  for(int i = 3; i <= c->n; ++i)
  {
    while(ccw(pts[top-1], pts[top], pts[i]) < 0)
    {
      top--;
    }
    top++;

    {
      float (*temp)[3] = malloc(sizeof(float) * 3);
      memcpy(temp, pts[i], sizeof(float) * 3);
      
      memcpy(pts[i], pts[top], sizeof(float) * 3);
      memcpy(pts[top], temp, sizeof(float) * 3);
    }
  }

  while(ccw(pts[top-1], pts[top], pts[0]) < 0)
  {
    top--;
  }

  Polygon* poly = malloc(sizeof(Polygon));
  poly->p = pts;
  poly->n = top + 1;
  return poly;
}

