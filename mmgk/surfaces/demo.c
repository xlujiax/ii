#include "demo.h"

Surface* demo1(void)
{
  Surface* s = surface_create_uniform(4, 4);
  
  for(int i = 0; i < 16; i++)
  {
    s->control[i] = -3.0;
  }
  return s;
}

Surface* demo(void)
{
  /* return demo2(); */
  /* return demo3(); */
  /* return demo1(); */
  return demo1();
}
