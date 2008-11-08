// Maciej Pacut
#include <stdio.h>
#include <stdlib.h>
#include <float.h>

union accessible_float {
 unsigned long int ui;
 float f;
};

struct eight_bytes
{
       unsigned long int a;
       unsigned long int b;
};

union accessible_double {
 struct eight_bytes dd;
 double d;
};

int main(int argc, char *argv[])
{
    {
     union accessible_float af;
     float f;
    
     for(af.ui = 0; ; ++af.ui)
     {
              //printf("%.50f\n",af.f);
              f = af.f;
              if(f + 1.0f == f)
              {
                   af.ui--;
                   printf("float y: %e\n",af.f);
                   break;
               }
     }
    
     for(af.ui = 0; ; ++af.ui)
     {
              //printf("%.50f\n",af.f);
              f = af.f;
              if(f + 1.0f == 1.0f)
              {
                   af.ui--;
                   printf("float x: %e\n",af.f);
                   break;
               }
     }
     }
    {
     union accessible_double ad;
     double d;
     for(ad.dd.a = 0; ; ++ad.dd.a)
     {
      for(ad.dd.b = 0; ; ++ad.dd.b)
     {
              //printf("%.50f\n",ad.d);
              d = ad.d;
              if(d + 1.0f == d)
              {
                   ad.dd.b--;
                   printf("double y: %e\n",ad.d);
                   break;
               }
     }
               if(d + 1.0f == d)
              {                   
                   break;
               }
     }
    
     for(ad.dd.a = 0; ; ++ad.dd.a)
     {
      for(ad.dd.b = 0; ; ++ad.dd.b)
     {
              //printf("%.50f\n",ad.d);
              d = ad.d;
              if(d + 1.0 == 1.0)
              {
                   ad.dd.b--;
                   printf("double x: %e\n",ad.d);
                   break;
               }
      }
      
              if(d + 1.0 == 1.0)
              {
                   break;
               }
      }
     }
    
    system("PAUSE");
    return 0;
}
