#include "demo.h"

Surface* demo1(void)
{
  int knots = 5;
  Surface* surf = surface_create_uniform(4, knots, knots);
  surf->wireframed = 0;
  
  for(int s = 0; s < knots; s++)
    for(int t = 0; t < knots; t++)
    {
      surf->control[s*surf->sStride + t*surf->tStride] = 2.0*((GLfloat)s - 1.5);
      surf->control[s*surf->sStride + t*surf->tStride + 1] = 2.0*((GLfloat)t - 1.5);
      surf->control[s*surf->sStride + t*surf->tStride + 2] = ((s == 1 || s == 2) && (t == 1 || t == 2)) ? 3.0 : -3.0;
    }
  return surf;
}

Surface* demo2(void)
{
  int knots = 5;
  Surface* surf = surface_create_uniform(4, knots, knots);
  surf->wireframed = 0;
  
  for(int s = 0; s < knots; s++)
    for(int t = 0; t < knots; t++)
    {
      surf->control[s*surf->sStride + t*surf->tStride] = 2.0*((GLfloat)s - 1.5);
      surf->control[s*surf->sStride + t*surf->tStride + 1] = 2.0*((GLfloat)t - 1.5);
      surf->control[s*surf->sStride + t*surf->tStride + 2] = -3.0f;
    }
  return surf;
}

Surface* demo(void)
{
  /* return demo2(); */
  /* return demo3(); */
  /* return demo1(); */
  return demo1();
}
