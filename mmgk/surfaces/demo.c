#include "demo.h"

Surface* demo1(void)
{
  Surface* surf = surface_create_uniform(4, 4);
  
  for(int s = 0; s < 4; s++)
    for(int t = 0; t < 4; t++)
    {
      surf->control[s*surf->sStride + t*surf->tStride] = 2.0*((GLfloat)s - 1.5);
      surf->control[s*surf->sStride + t*surf->tStride + 1] = 2.0*((GLfloat)t - 1.5);
      surf->control[s*surf->sStride + t*surf->tStride + 2] = -3.0;
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
