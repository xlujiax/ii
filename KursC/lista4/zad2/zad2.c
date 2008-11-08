// Maciej Pacut
#include <stdio.h>
#include <malloc.h>

#include "quicksort.h"
#include "sorttest.h"
#include "list.h"

// dla wrappera qsort
int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}
// wrapper dla qsort
void qsort_std(int* arr, int sz)
{
     qsort(arr, sz, sizeof(int), compare);
}

float average_time_list(int sz, int times)
{
       clock_t begin = clock();
       int i;
       for(i = 0; i < times; ++i)
       {
        struct List* lst = generate_lst(sz);
        lst = quicksort(lst);
        iterate(lst,cleanup);
        }
       clock_t end = clock();
       return ((float)(end - begin)) / ((float)CLOCKS_PER_SEC);
}

void test(int sz)
{
  printf("test dla %d:\n", sz);
  printf("standardowy: %f\n", average_time(qsort_std, sz, 100));
  printf("wlasny:      %f\n", average_time_list(sz, 100));
}

int main(int argc, char *argv[])
{
    srand(time(0));
    test(100);
    test(1000);
    test(10000);
    test(100000);
  system("pause");
  return 0;
}
