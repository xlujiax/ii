#include "sorttest.h"

int* generate(int sz)
{
     int i;
     int* arr = malloc(sizeof(int) * sz);
     for(i = 0; i < sz; ++i)
           arr[i] = rand();
     return arr;
 }
 
 int sortedp(int* arr, int sz)
 {
     int i;
     for(i = 0; i < sz - 1; ++i)
           if(arr[i] > arr[i + 1])
                     return 0;
     return 1;
 }
 
 int permp(int* src, int* res, int sz)
 {
     // traktujê zero jako wartoœæ specjaln¹
     int src_zeros = 0;
     int res_zeros = 0;
     int i,j, flag;
     for(i = 0; i < sz; ++i)
           if(src[i] == 0)
                     ++src_zeros;
           if(res[i] == 0)
                     ++res_zeros;
                     
     if(src_zeros != res_zeros)
                  return 0;
     
     // sprawdzam czy ka¿dy element z src ma swój odpowiednik w res
     // aby nie przypisaæ dwum elementom z src jednego elementu z res
     // zerujê element kojarzony w res
     for(i = 0; i < sz; ++i)
     {
           flag = 0;
           for(j = 0; j < sz; ++j)
                 if(src[i] == res[j])
                 {
                           res[j] = 0;
                           flag = 1;
                           break;
                 }
           if(!flag)
                    return 0;
     }
     return 1;
 }

float average_time(void (*sort)(int*, int), int sz, int times)
{
       clock_t begin = clock();
       int i;
       for(i = 0; i < times; ++i)
       {
             int* arr = generate(sz);
             sort(arr, sz);
             free(arr);
       }
       clock_t end = clock();
       
       return ((float)(end - begin)) / ((float)CLOCKS_PER_SEC);
}
